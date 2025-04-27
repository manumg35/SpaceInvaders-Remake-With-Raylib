#include "Game.h"
#include <string>

void Game::Init()
{
    InitWindow(screenWidth, screenHeight, "Space Invaders Remake using ECS");

    SetTargetFPS(targetFPS);

    LoadTextures();
    CreateEntities();
}

void Game::Run()
{
    while(!WindowShouldClose())
    {
        switch (gameState)
        {
        case GameStateType::Paused:
            if(IsKeyPressed(KEY_SPACE))
                gameState = GameStateType::Playing;
            Render();
            break;

        case GameStateType::Playing:
            Update();
            break;

        case GameStateType::GameOver:
            if(IsKeyPressed(KEY_SPACE))
                gameState = GameStateType::Restarting;
            Render(true);
            break;

        case GameStateType::Restarting:
            Restart();
            break;

        default:
            break;
        }
    }
}

void Game:: Update()
{
    std::vector<CollisionEvent> colEvents;
    std::vector<GameEvent> gameEvents;

    //Player Controller + INPUT
    pcSystem.Update(*player, inputSystem.HandleInput(), shootEvents);

    float deltaTime = GetFrameTime();    

    //AI
    aiSystem.Update(entities, shootEvents, gameData);

    //MANAGE BULLETS
    bulletSystem.Update(entities, shootEvents);
    
    //MOVEMENT
    movementSystem.Update(entities, deltaTime);

    //COLLISIONS
    colliderSystem.UpdateColliders(entities);
    
    colliderSystem.CheckCollisions(entities, colEvents);
    colliderSystem.HandleCollisions(entities, colEvents, gameEvents);

    //MANAGE GAME EVENTS
    gameManager.Update(gameEvents, gameData, gameState);
    
    Render();
}

void Game::Render(bool renderJustUI)
{    
    BeginDrawing();
    ClearBackground(BLACK);

    if(!renderJustUI){
        //Render entities
        renderSystem.Render(entities);
    }
    //Render UI
    uiSystem.Render(gameData, gameState);

    EndDrawing();
}

void Game::Close()
{
    entities.clear();
    shootEvents.clear();

    player = nullptr;

    UnloadTextures();
    
    CloseWindow();
}

void Game::Restart()
{
    entities.clear();
    shootEvents.clear();

    gameData.nDeadEnemies = 0;
    gameData.playerHealth = 3;
    gameData.score = 0;

    CreateEntities();

    gameState = GameStateType::Playing;
}

void Game::LoadTextures()
{
    playerTexture = LoadTexture("textures/spaceship.png");
    playBulletTexture = LoadTexture("textures/bullet.png");
    enemyTexture = LoadTexture("textures/enemy1.png");
    enemyBulletTexture = LoadTexture("textures/enemyBullet.png");
}
void Game::UnloadTextures()
{
    UnloadTexture(playerTexture);
    UnloadTexture(playBulletTexture);
    UnloadTexture(enemyTexture);
    UnloadTexture(enemyBulletTexture);
}
void Game::CreateEntities()
{
    //Create player
    player = std::make_shared<Entity>();
    player->AddComponent<TransformComponent>(200,500);
    player->AddComponent<ColliderComponent>(200, 500, 32, 32, 0, 0);
    player->AddComponent<MovementComponent>(0,0);
    player->AddComponent<RenderComponent>(playerTexture);
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
            enemy.AddComponent<RenderComponent>(enemyTexture);
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
        bullet.AddComponent<RenderComponent>(playBulletTexture);
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
        bullet.AddComponent<RenderComponent>(enemyBulletTexture);
        bullet.AddComponent<TagComponent>(EntityType::EnemyBullet);
        bullet.isActive = false;
        entities.push_back(bullet);
    }
}
