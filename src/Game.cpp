#include "Game.h"
#include <string>

void Game::Init()
{
    InitWindow(screenWidth, screenHeight, "Space Invaders Remake using ECS");

    SetTargetFPS(targetFPS);

    //Create player
    player = std::make_shared<Entity>();
    player->AddComponent<TransformComponent>(200,500);
    player->AddComponent<MovementComponent>(0,0);
    player->AddComponent<RenderComponent>(LoadTexture("textures/spaceship.png"));
    player->AddComponent<TagComponent>(EntityType::Player);
    entities.push_back(*player);

    //Create enemies
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
            enemy.AddComponent<TagComponent>(EntityType::Enemy);
            entities.push_back(std::move(enemy));
        }
    }

    //Create bullets
    Entity bullet;
    bullet.AddComponent<TransformComponent>(0, 0);
    bullet.AddComponent<ColliderComponent>(0, 0, 5, 12, 14, 10);
    bullet.AddComponent<MovementComponent>(0, -500);
    bullet.AddComponent<BulletComponent>();
    bullet.AddComponent<RenderComponent>(LoadTexture("textures/bullet.png"));
    bullet.AddComponent<TagComponent>(EntityType::PlayerBullet);
    entities.push_back(bullet);

    Entity bullet2;
    bullet2.AddComponent<TransformComponent>(0, 0);
    bullet2.AddComponent<ColliderComponent>(0, 0, 5, 12, 14, 10);
    bullet2.AddComponent<MovementComponent>(0, -500);
    bullet2.AddComponent<BulletComponent>();
    bullet2.AddComponent<RenderComponent>(LoadTexture("textures/bullet.png"));
    bullet2.AddComponent<TagComponent>(EntityType::PlayerBullet);
    entities.push_back(bullet2);
}


void Game::Run()
{
    while(!WindowShouldClose())
    {
        
        float deltaTime = GetFrameTime();

        //INPUT
        pcSystem.Update(*player, inputSystem.HandleInput(), shootEvents);

        //AI
        aiSystem.Update(entities);

        //MANAGE BULLETS
        bulletSystem.Update(entities, shootEvents);
        
        //MOVEMENT
        movementSystem.Update(entities, deltaTime);

        //COLLISIONS
        colliderSystem.UpdateColliders(entities);

        colliderSystem.CheckCollisions(entities);

        BeginDrawing();
        ClearBackground(BLACK);

        //RENDER
        renderSystem.Render(entities);

        DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 18, WHITE);
        // DrawText(typeid(RenderSystem).name(), 0, 0, 18, WHITE);
        // DrawText(typeid(InputSystem).name(), 0, 18, 18, WHITE);
        // DrawText(typeid(MovementComponent).name(), 0, 36, 18, WHITE);
        EndDrawing();
    }
    
    CloseWindow();
}