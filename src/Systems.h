#pragma once
#include "raylib.h"
#include "ECS.h"
#include "Components.h"

struct GameData 
{
    int score{};
    int highScore{};
    int playerHealth{3};
    int nDeadEnemies{0};
};

enum class GameStateType
{
    Paused,
    Playing,
    GameOver,
    Restarting
};

struct ShootEvent
{
    Vector2 position;
    float ySpeed;
    int yDirection;
    EntityType bulletType;
};

struct CollisionEvent{
    int entityAIndex;
    int entityBIndex;
};

enum class PlayerCommand
{
    MoveLeft,
    MoveRight,
    Shoot,
    Stop
};

enum class GameEventType
{
    PlayerHit,
    EnemyKilled,
};

struct GameEvent
{
    GameEventType type;
};

class InputSystem
{
public:
    std::vector<PlayerCommand> HandleInput()
    {
        std::vector<PlayerCommand> commands;

        if(IsKeyDown(KEY_D))
            commands.push_back(PlayerCommand::MoveRight);
        else if(IsKeyDown(KEY_A))
            commands.push_back(PlayerCommand::MoveLeft);
        else
            commands.push_back(PlayerCommand::Stop);

        if(IsKeyPressed(KEY_SPACE))
            commands.push_back(PlayerCommand::Shoot);
        
        return commands;
    }
};

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

class ColliderSystem
{
public:
    void UpdateColliders(std::vector<Entity>& entities)
    {
        for(auto& entity : entities)
        {
            if(!entity.isActive)
                continue;
            auto* pos = entity.GetComponent<TransformComponent>();
            auto* col = entity.GetComponent<ColliderComponent>();

            if(!pos || !col)
                continue;
            col->rect.x = pos->position.x + col->paddingRight;
            col->rect.y = pos->position.y + col->paddingBottom;

            //DEBUG COLLIDER
            //DrawRectangle(col->rect.x, col->rect.y, col->rect.width, col->rect.height, BLUE);
        }
    }

    void CheckCollisions(std::vector<Entity>& entities, std::vector<CollisionEvent>& colEvents)
    {
        for(int i = 0; i<entities.size(); i++)
        {
            if(!entities[i].isActive)
                continue;
            
            auto* colA = entities[i].GetComponent<ColliderComponent>();
            if(!colA)
                continue;

            
            for(int j = i+1; j <entities.size(); j++)
            {
                if(!entities[j].isActive)
                continue;
            
                auto* colB = entities[j].GetComponent<ColliderComponent>();
                if(!colB)
                    continue;

                if(CheckCollisionRecs(colA->rect, colB->rect))
                {
                    colEvents.push_back({i, j});
                }
            }
        }
    }

    void HandleCollisions(std::vector<Entity>& entities, std::vector<CollisionEvent>& colEvents, std::vector<GameEvent>& gameEvents)
    {
        for(auto& event: colEvents)
        {
            Entity& a = entities[event.entityAIndex];
            Entity& b = entities[event.entityBIndex];

            //Collision symmetry
            ResolveCollisions(a,b, gameEvents);
            ResolveCollisions(b,a, gameEvents);
        }
        colEvents.clear();
    }

    void ResolveCollisions(Entity&a , Entity&b, std::vector<GameEvent>& gameEvents)
    {
        auto* tagA = a.GetComponent<TagComponent>();
        auto* tagB = b.GetComponent<TagComponent>();
            
        if(!tagA || !tagB)
            return;
            
        //Player collision with enemy bullet
        if(tagA->type == EntityType::Player)
        {
            if(tagB->type == EntityType::EnemyBullet)
            {
                b.isActive = false;
                
                //Check health
                auto* health = a.GetComponent<HealthComponent>();
                if(!health)
                    return;

                health->currentHealth--;
                if(health->currentHealth<1)
                    a.isActive = false;

                gameEvents.push_back({GameEventType::PlayerHit});
            }
        }
        //Player bullet collision
        else if(tagA->type == EntityType::PlayerBullet)
        {
            if(tagB->type == EntityType::EnemyBullet)
            {
                a.isActive = false;
                b.isActive = false;
            }
            else if(tagB->type == EntityType::Enemy)
            {
                a.isActive = false;
                b.isActive = false;
                //AddScore Event
                gameEvents.push_back({GameEventType::EnemyKilled});
            }
        }                
    }
};

class AISystem
{
public:
    void Update(std::vector<Entity>& entities, std::vector<ShootEvent>& shootEvents, const GameData& gameData)
    {
        float maxX{-1.f};
        float minX{450.f};

        bool reverseDir = false;
        for(auto& entity : entities)
        {
            if(!entity.isActive)
                continue;
            auto* pos = entity.GetComponent<TransformComponent>();
            auto* mov = entity.GetComponent<MovementComponent>();
            auto* ai = entity.GetComponent<AIComponent>();

            if(pos && mov && ai)
            {
                maxX = std::max(maxX, pos->position.x);
                minX = std::min(minX, pos->position.x);

                if(maxX > 368 || minX < 0)
                {
                    reverseDir = true;
                    maxX = 0.f;
                    minX = 450.f;
                    break;
                }
            }
        }

        for(auto& entity : entities)
        {
            if(!entity.isActive)
                continue;

            auto* mov = entity.GetComponent<MovementComponent>();
            auto* pos = entity.GetComponent<TransformComponent>();
            auto* ai = entity.GetComponent<AIComponent>();
            if(!ai || !pos || !mov)
                continue;

            if(reverseDir)
            {
                pos->position.y += 32;
                ai->xDir *= -1;
            }
            // increase bullet spawn rate probability as fewer enemies are alive
            if (GetRandomValue(0, 4000) < gameData.nDeadEnemies) 
                shootEvents.push_back({pos->position, 150, 1, EntityType::EnemyBullet});
            // increase speed as fewer enemies are alive
            mov->velocity.x = ai->xDir * (50 + (20 * gameData.nDeadEnemies));
        }
    }
};

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

class BulletSystem
{
public:

    void Update(std::vector<Entity>& bullets, std::vector<ShootEvent>& shootEvents)
    {
        //check if should spawn new bullets
        for(auto& shootEv: shootEvents)
        {
            for(auto& bullet: bullets)
            {
                auto* bulComp = bullet.GetComponent<BulletComponent>();
                auto* bulPos = bullet.GetComponent<TransformComponent>();
                auto* bulMov = bullet.GetComponent<MovementComponent>();
                auto* tag = bullet.GetComponent<TagComponent>();

                if(!bulComp || tag->type != shootEv.bulletType)
                    continue;
                if(bullet.isActive)
                    continue;

                bullet.isActive = true;
                
                bulPos->position = shootEv.position;           
                bulMov->velocity.y = shootEv.ySpeed * shootEv.yDirection;
                
                break;
            }
        }
        shootEvents.clear();

        //check if bullet should be active
        for (auto& bullet : bullets) {
            auto* bulPos = bullet.GetComponent<TransformComponent>();
            auto* bulComp = bullet.GetComponent<BulletComponent>();
            auto* bulMov = bullet.GetComponent<MovementComponent>();

            if(!bulComp || !bulPos || !bulMov)
                continue;
            
            if(bulPos->position.y < -50 || bulPos->position.y > 600)
            {
                bullet.isActive = false;
                bulMov->velocity.y = 0;
            }
        }

    }
};

class RenderSystem 
{
public:
    void Render(std::vector<Entity>& entities) {
        for (auto& entity : entities) {
            if(!entity.isActive)
                continue;
            auto* pos = entity.GetComponent<TransformComponent>();
            auto* render = entity.GetComponent<RenderComponent>();
            if (pos && render)
                DrawTexture(render->texture, pos->position.x, pos->position.y, render->textureTint);
        }
    }
};

class GameManagerSystem
{
public:
    void Update(std::vector<GameEvent>& gameEvents, GameData& gameData, GameStateType& gameState)
    {
        for(auto& gameEvent : gameEvents)
        {
            switch (gameEvent.type)
            {
            case GameEventType::EnemyKilled:
                gameData.score+=100;
                gameData.nDeadEnemies++;
                if(gameData.score>gameData.highScore)
                    gameData.highScore = gameData.score;
                break;

            case GameEventType::PlayerHit:
            {
                gameData.playerHealth--;
                if(gameData.playerHealth<1)
                    gameState = GameStateType::GameOver;
                break;
            }
            default:
                break;
            }

        }
        gameEvents.clear();
    }
};


class UISystem
{
public:
    void Render(GameData& gameData, GameStateType gameState)
    {
        
        switch (gameState)
        {
        case GameStateType::Paused:
            DrawText("Press the space bar to start", 50, 450, 20, WHITE);
            DrawText(TextFormat("Hi-Score: %i", gameData.highScore), 50, 400, 20, WHITE);
            break;
        case GameStateType::GameOver:
            DrawText("Press the space bar to restart", 50, 450, 20, WHITE);
            DrawText("You lost! :c", 50, 425, 20, WHITE);
            DrawText(TextFormat("Your score: %i", gameData.score), 50, 400, 20, WHITE);
            DrawText(TextFormat("Hi-Score: %i", gameData.highScore), 50, 375, 20, WHITE);
            break;
        default:
            DrawText(TextFormat("Score: %i", gameData.score), 10, 10, 20, WHITE);
            DrawText(TextFormat("Hi-Score: %i", gameData.highScore), 10, 30, 20, WHITE);
            break;
        }
    }

};