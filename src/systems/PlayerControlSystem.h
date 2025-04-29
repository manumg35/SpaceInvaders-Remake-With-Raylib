#pragma once
#include "../ECS.h"
#include "../core/PlayerCommand.h"
#include "../events/ShootEvent.h"
#include "../components/MovementComponent.h"
#include "../components/TransformComponent.h"

class PlayerControlSystem
{
public:
    void Update(Entity& player, std::vector<PlayerCommand> commands, std::vector<ShootEvent>& shootEvents)
    {
        auto* mov = player.GetComponent<MovementComponent>();
        auto* pos = player.GetComponent<TransformComponent>();

        for(auto& command : commands)
        {
            switch (command)
            {
            case PlayerCommand::MoveRight:
                mov->velocity.x = 150;
                break;
            
            case PlayerCommand::MoveLeft:
                mov->velocity.x = -150;
                break;

            case PlayerCommand::Stop:
                mov->velocity.x = 0;
                break;

            case PlayerCommand::Shoot:
            {
                shootEvents.push_back({pos->position, 500, -1, EntityType::PlayerBullet});
                break;
            }
            default:
                break;
            }
        }
    }
};