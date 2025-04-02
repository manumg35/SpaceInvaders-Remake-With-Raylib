#pragma once
#include "raylib.h"
#include "ECS.h"
#include "Components.h"

class InputSystem
{
public:
    void HandleInput(Entity& player)
    {
        auto * mov = player.GetComponent<MovementComponent>();
        
        if(IsKeyDown(KEY_D))
            mov->velocity.x = 200;
        else if(IsKeyDown(KEY_A))
            mov->velocity.x = -200;
        else
            mov->velocity.x = 0;

        if(IsKeyPressed(KEY_SPACE))
        {
            // shoot
        }
    }
};

class MovementSystem
{
public:
    void Update(std::vector<Entity>& entities, float deltaTime)
    {
        for (auto& entity : entities) {
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

class RenderSystem 
{
public:
    void Render(std::vector<Entity>& entities) {
        for (auto& entity : entities) {
            auto* pos = entity.GetComponent<TransformComponent>();
            auto* sprite = entity.GetComponent<SpriteComponent>();
            if (pos && sprite)
                DrawTexture(sprite->texture, pos->position.x, pos->position.y, WHITE);
        }
    }
};