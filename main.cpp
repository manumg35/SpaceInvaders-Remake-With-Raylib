#include "raylib.h"
#include "src/ECS.h"
#include "src/Components.h"
#include "src/Systems.h"

int main()
{
    InitWindow(400, 600, "Space Invaders Remake using ECS");
    SetTargetFPS(60);

    Entity player;
    player.AddComponent<TransformComponent>(150,150);
    player.AddComponent<SpriteComponent>(LoadTexture("textures/spaceship.png"));
    player.AddComponent<MovementComponent>(0,0);

    std::vector<Entity> entities;
    entities.push_back(player);

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

        EndDrawing();
    }
    
    CloseWindow();
}