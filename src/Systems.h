#pragma once
#include "raylib.h"
#include "ECS.h"
#include "Components.h"

class InputSystem
{
public:
    void HandleInput(Entity& player, Entity& bullet)
    {
        auto * mov = player.GetComponent<MovementComponent>();
        auto * pos = player.GetComponent<TransformComponent>();


        auto * bul = bullet.GetComponent<BulletComponent>();
        auto * bulPos = bullet.GetComponent<TransformComponent>();

        if(IsKeyDown(KEY_D))
            mov->velocity.x = 150;
        else if(IsKeyDown(KEY_A))
            mov->velocity.x = -150;
        else
            mov->velocity.x = 0;

        if(IsKeyPressed(KEY_SPACE))
        {
            if(bul && bulPos)
            {
                bulPos->position.x = pos->position.x;
                bulPos->position.y = pos->position.y;


            }
        }
    }
};

class ColliderSystem
{
public:
    void UpdateColliders(std::vector<Entity>& entities)
    {
        for(auto& entity : entities)
        {
            auto* pos = entity.GetComponent<TransformComponent>();
            auto* col = entity.GetComponent<ColliderComponent>();

            col->rect.x = pos->position.x + col->paddingRight;
            col->rect.y = pos->position.y + col->paddingBottom;

            DrawRectangle(col->rect.x, col->rect.y, col->rect.width, col->rect.height, BLUE);
        }

    }
    void CheckCollisions(std::vector<Entity>& entities1, std::vector<Entity>& entities2)
    {

        for(auto& bullet : entities1)
        {
            auto* collider = bullet.GetComponent<ColliderComponent>();

            for(auto& enemy : entities2)
            {
                auto* otherCollider = enemy.GetComponent<ColliderComponent>();
                auto* render = enemy.GetComponent<RenderComponent>();

                if(CheckCollisionRecs(collider->rect, otherCollider->rect))
                {
                    render->textureTint = RED;
                }
            }
        }
    }
};

class AISystem
{
public:
    void Update(std::vector<Entity>& enemies)
    {
        float maxX{-1.f};
        float minX{450.f};
        float minY{600.f};

        for(auto& enemy : enemies)
        {
            auto* pos = enemy.GetComponent<TransformComponent>();
            auto* mov = enemy.GetComponent<MovementComponent>();
            auto* ai = enemy.GetComponent<AIComponent>();

            if(pos && mov && ai)
            {
                maxX = std::max(maxX, pos->position.x);
                minX = std::min(minX, pos->position.x);

                minY = std::min(minY, pos->position.y);

                if(maxX > 368)
                    ai->xDir = -1;
                
                if(minX < 0)
                    ai->xDir = 1;

                mov->velocity.x = (10 + (ai->currentSpeed * minY)) * ai->xDir;
            }
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
            auto* render = entity.GetComponent<RenderComponent>();
            if (pos && render)
                DrawTexture(render->texture, pos->position.x, pos->position.y, render->textureTint);
        }
    }
};