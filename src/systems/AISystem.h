#pragma once
#include "../ECS.h"
#include "../components/TransformComponent.h"
#include "../components/MovementComponent.h"
#include "../components/AIComponent.h"
#include "../events/ShootEvent.h"
#include "../core/GameData.h"


class AISystem
{
public:
    void Update(std::vector<Entity>& entities, std::vector<ShootEvent>& shootEvents, const GameData& gameData)
    {
        float maxX{-1.f};
        float minX{450.f};

        bool reverseDir = false;
        for(auto& entity : entities)
        {
            if(!entity.isActive)
                continue;
            auto* pos = entity.GetComponent<TransformComponent>();
            auto* mov = entity.GetComponent<MovementComponent>();
            auto* ai = entity.GetComponent<AIComponent>();

            if(pos && mov && ai)
            {
                maxX = std::max(maxX, pos->position.x);
                minX = std::min(minX, pos->position.x);

                if(maxX > 368 || minX < 0)
                {
                    reverseDir = true;
                    maxX = 0.f;
                    minX = 450.f;
                    break;
                }
            }
        }

        for(auto& entity : entities)
        {
            if(!entity.isActive)
                continue;

            auto* mov = entity.GetComponent<MovementComponent>();
            auto* pos = entity.GetComponent<TransformComponent>();
            auto* ai = entity.GetComponent<AIComponent>();
            if(!ai || !pos || !mov)
                continue;

            if(reverseDir)
            {
                pos->position.y += 32;
                ai->xDir *= -1;
            }
            // increase bullet spawn rate probability as fewer enemies are alive
            if (GetRandomValue(0, 2500) < gameData.nDeadEnemies) 
                shootEvents.push_back({pos->position, 150, 1, EntityType::EnemyBullet});
            // increase speed as fewer enemies are alive
            mov->velocity.x = ai->xDir * (10 +gameData.nDeadEnemies);
        }
    }
};