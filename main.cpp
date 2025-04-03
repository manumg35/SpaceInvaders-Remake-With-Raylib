#include "raylib.h"
#include "src/ECS.h"
#include "src/Components.h"
#include "src/Systems.h"
#include <string>

int main()
{
    InitWindow(400, 600, "Space Invaders Remake using ECS");

    SetTargetFPS(60);

    std::vector<Entity> entities;
    std::vector<Entity> enemies;
    std::vector<Entity> bullets;
    
    Entity player;
    player.AddComponent<TransformComponent>(200,500);
    
    player.AddComponent<MovementComponent>(0,0);
    player.AddComponent<RenderComponent>(LoadTexture("textures/spaceship.png"));
    
    entities.push_back(player);

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<8; j++)
        {
            Entity enemy;
            enemy.AddComponent<TransformComponent>(50 + 32 * j, 100 + 32 * i);
            enemy.AddComponent<ColliderComponent>(50 + 32 * j, 100 + 32 * i, 28, 16, 0, 10);
            enemy.AddComponent<AIComponent>();
            enemy.AddComponent<MovementComponent>(0,0);
            enemy.AddComponent<RenderComponent>(LoadTexture("textures/enemy1.png"));
            enemies.push_back(enemy);
        }
    }

    Entity bullet;
    bullet.AddComponent<TransformComponent>(200, 100);
    bullet.AddComponent<ColliderComponent>(0, 0, 5, 12, 14, 10);
    bullet.AddComponent<MovementComponent>(0, -100);
    bullet.AddComponent<BulletComponent>(-1);
    bullet.AddComponent<RenderComponent>(LoadTexture("textures/bullet.png"));
    bullets.push_back(bullet);


    RenderSystem renderSystem;
    InputSystem inputSystem;
    MovementSystem movementSystem;
    AISystem aiSystem;
    ColliderSystem colliderSystem;

    while(!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();


        inputSystem.HandleInput(player, bullet);

        aiSystem.Update(enemies);

        movementSystem.Update(entities, deltaTime);
        movementSystem.Update(enemies, deltaTime);
        movementSystem.Update(bullets, deltaTime);

        colliderSystem.UpdateColliders(enemies);
        colliderSystem.UpdateColliders(bullets);

        colliderSystem.CheckCollisions(bullets, enemies);

        BeginDrawing();
        ClearBackground(BLACK);

        renderSystem.Render(entities);
        renderSystem.Render(enemies);
        renderSystem.Render(bullets);

        DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 18, WHITE);
        // DrawText(typeid(RenderSystem).name(), 0, 0, 18, WHITE);
        // DrawText(typeid(InputSystem).name(), 0, 18, 18, WHITE);
        // DrawText(typeid(MovementComponent).name(), 0, 36, 18, WHITE);
        EndDrawing();
    }
    
    CloseWindow();
}