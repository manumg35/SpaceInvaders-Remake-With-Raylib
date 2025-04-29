#pragma once
#include "../ECS.h"
#include "../events/CollisionEvent.h"
#include "../components/TransformComponent.h"
#include "../components/ColliderComponent.h"
#include "../components/TagComponent.h"
#include "../components/HealthComponent.h"
#include "../events/GameEvents.h"


class ColliderSystem
{
public:
    void UpdateColliders(std::vector<Entity>& entities)
    {
        for(auto& entity : entities)
        {
            if(!entity.isActive)
                continue;
            auto* pos = entity.GetComponent<TransformComponent>();
            auto* col = entity.GetComponent<ColliderComponent>();

            if(!pos || !col)
                continue;
            col->rect.x = pos->position.x + col->paddingRight;
            col->rect.y = pos->position.y + col->paddingBottom;

            //DEBUG COLLIDER
            //DrawRectangle(col->rect.x, col->rect.y, col->rect.width, col->rect.height, BLUE);
        }
    }

    void CheckCollisions(std::vector<Entity>& entities, std::vector<CollisionEvent>& colEvents)
    {

        for(size_t i = 0; i<entities.size(); i++)
        {
            if(!entities[i].isActive)
                continue;
            
            auto* colA = entities[i].GetComponent<ColliderComponent>();
            if(!colA)
                continue;

            
            for(size_t j = i+1; j <entities.size(); j++)
            {
                if(!entities[j].isActive)
                continue;
            
                auto* colB = entities[j].GetComponent<ColliderComponent>();
                if(!colB)
                    continue;

                if(CheckCollisionRecs(colA->rect, colB->rect))
                {
                    colEvents.push_back({static_cast<int>(i), static_cast<int>(j)});
                }
            }
        }
    }

    void HandleCollisions(std::vector<Entity>& entities, std::vector<CollisionEvent>& colEvents, std::vector<GameEvent>& gameEvents)
    {
        for(auto& event: colEvents)
        {
            Entity& a = entities[event.entityAIndex];
            Entity& b = entities[event.entityBIndex];

            //Collision symmetry
            ResolveCollisions(a,b, gameEvents);
            ResolveCollisions(b,a, gameEvents);
        }
        colEvents.clear();
    }

    void ResolveCollisions(Entity&a , Entity&b, std::vector<GameEvent>& gameEvents)
    {
        auto* tagA = a.GetComponent<TagComponent>();
        auto* tagB = b.GetComponent<TagComponent>();
            
        if(!tagA || !tagB)
            return;
            
        //Player collision with enemy bullet
        if(tagA->type == EntityType::Player)
        {
            if(tagB->type == EntityType::EnemyBullet)
            {
                b.isActive = false;
                
                //Check health
                auto* health = a.GetComponent<HealthComponent>();
                if(!health)
                    return;

                health->currentHealth--;
                if(health->currentHealth<1)
                    a.isActive = false;

                gameEvents.push_back({GameEventType::PlayerHit, a});
            }
        }
        //Player bullet collision
        else if(tagA->type == EntityType::PlayerBullet)
        {
            if(tagB->type == EntityType::EnemyBullet)
            {
                a.isActive = false;
                b.isActive = false;
            }
            else if(tagB->type == EntityType::Enemy)
            {
                a.isActive = false;
                b.isActive = false;
                //AddScore Event
                gameEvents.push_back({GameEventType::EnemyKilled, b});
            }
        }                
    }
};