#include "Game.h"
#include <string>

void Game::Init()
{
    InitWindow(screenWidth, screenHeight, "Space Invaders Remake using ECS");

    SetTargetFPS(targetFPS);

    //Create player
    player = std::make_shared<Entity>();
    player->AddComponent<TransformComponent>(200,500);
    player->AddComponent<ColliderComponent>(200, 500, 32, 32, 0, 0);
    player->AddComponent<MovementComponent>(0,0);
    player->AddComponent<RenderComponent>(LoadTexture("textures/spaceship.png"));
    player->AddComponent<TagComponent>(EntityType::Player);
    player->AddComponent<HealthComponent>(3);
    entities.push_back(*player);

    //Create enemies
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<5; j++)
        {
            Entity enemy;
            enemy.AddComponent<TransformComponent>(50 + 32 * j, 100 + 32 * i);
            enemy.AddComponent<ColliderComponent>(50 + 32 * j, 100 + 32 * i, 28, 16, 0, 10);
            enemy.AddComponent<AIComponent>();
            enemy.AddComponent<MovementComponent>(0,0);
            enemy.AddComponent<RenderComponent>(LoadTexture("textures/enemy1.png"));
            enemy.AddComponent<TagComponent>(EntityType::Enemy);
            enemy.AddComponent<HealthComponent>(1);
            entities.push_back(std::move(enemy));
        }
    }

    //Create player bullets
    for(int i=0; i<2; i++)
    {
        Entity bullet;
        bullet.AddComponent<TransformComponent>(0, 0);
        bullet.AddComponent<ColliderComponent>(0, 0, 5, 12, 14, 10);
        bullet.AddComponent<MovementComponent>(0, 0);
        bullet.AddComponent<BulletComponent>();
        bullet.AddComponent<RenderComponent>(LoadTexture("textures/bullet.png"));
        bullet.AddComponent<TagComponent>(EntityType::PlayerBullet);
        bullet.isActive = false;
        entities.push_back(bullet);
    }

    //Create enemy bullets
    for(int i=0; i<5; i++)
    {
        Entity bullet;
        bullet.AddComponent<TransformComponent>(0, 0);
        bullet.AddComponent<ColliderComponent>(0, 0, 5, 12, 14, 10);
        bullet.AddComponent<MovementComponent>(0, 0);
        bullet.AddComponent<BulletComponent>();
        bullet.AddComponent<RenderComponent>(LoadTexture("textures/enemyBullet.png"));
        bullet.AddComponent<TagComponent>(EntityType::EnemyBullet);
        bullet.isActive = false;
        entities.push_back(bullet);
    }
}

void Game::Run()
{
    while(!WindowShouldClose())
    {
        
        float deltaTime = GetFrameTime();

        //Player Controller + INPUT
        pcSystem.Update(*player, inputSystem.HandleInput(), shootEvents);

        //AI
        aiSystem.Update(entities, shootEvents);

        //MANAGE BULLETS
        bulletSystem.Update(entities, shootEvents);
        
        //MOVEMENT
        movementSystem.Update(entities, deltaTime);

        //COLLISIONS
        colliderSystem.UpdateColliders(entities);
        std::vector<CollisionEvent> collEvents;
        colliderSystem.CheckCollisions(entities, collEvents);
        colliderSystem.HandleCollisions(entities, collEvents);

        BeginDrawing();
        ClearBackground(BLACK);

        //RENDER
        renderSystem.Render(entities);

        //UI
        DrawText(std::to_string(GetFPS()).c_str(), 0, 0, 18, WHITE);        
        
        // DrawText(typeid(RenderSystem).name(), 0, 0, 18, WHITE);
        // DrawText(typeid(InputSystem).name(), 0, 18, 18, WHITE);
        // DrawText(typeid(MovementComponent).name(), 0, 36, 18, WHITE);
        EndDrawing();
    }
    
    
}

void Game::Close()
{
    entities.clear();
    shootEvents.clear();

    player = nullptr;
    CloseWindow();
}