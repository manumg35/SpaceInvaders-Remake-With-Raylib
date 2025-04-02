#include "raylib.h"
#include "src/ECS.h"
#include "src/Components.h"
#include "src/Systems.h"
#include <string>

int main()
{
    InitWindow(400, 600, "Space Invaders Remake using ECS");

    std::vector<Entity> entities;
    
    Entity player;
    player.AddComponent<TransformComponent>(200,500);
    player.AddComponent<SpriteComponent>(LoadTexture("textures/spaceship.png"));
    player.AddComponent<MovementComponent>(0,0);
    player.AddComponent<RectColliderComponent>(200, 500, 32, 32);
    
    entities.push_back(player);

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<8; j++)
        {
            Entity enemy;
            enemy.AddComponent<TransformComponent>(50 + 32 * j, 100 + 32 * i);
            enemy.AddComponent<SpriteComponent>(LoadTexture("textures/enemy1.png"));
            entities.push_back(enemy);
        }
    }

    RenderSystem renderSystem;
    InputSystem inputSystem;
    MovementSystem movementSystem;

    while(!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        inputSystem.HandleInput(player);
        movementSystem.Update(entities, deltaTime);

        BeginDrawing();
        ClearBackground(BLACK);

        renderSystem.Render(entities);
        //DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 18, WHITE);
        DrawText(typeid(RenderSystem).name(), 0, 0, 18, WHITE);
        DrawText(typeid(InputSystem).name(), 0, 18, 18, WHITE);
        DrawText(typeid(MovementComponent).name(), 0, 36, 18, WHITE);
        EndDrawing();
    }
    
    CloseWindow();
}