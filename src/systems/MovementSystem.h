#pragma once
#include "../ECS.h"
#include "../components/TransformComponent.h"
#include "../components/MovementComponent.h"

class MovementSystem
{
public:
    void Update(std::vector<Entity>& entities, float deltaTime)
    {
        for (auto& entity : entities) {
            if(!entity.isActive)
                continue;
            auto* pos = entity.GetComponent<TransformComponent>();
            auto * mov = entity.GetComponent<MovementComponent>();

            if (pos && mov) 
            {
                pos->position.x += mov->velocity.x * deltaTime;
                pos->position.y += mov->velocity.y * deltaTime;
            }
        }
    }
};