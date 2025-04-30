#pragma once
#include "../ECS.h"
#include "../events/GameEvents.h"
#include "../core/GameData.h"
#include "../core/GameState.h"
#include "../components/TransformComponent.h"
#include "../components/RenderComponent.h"
#include "../components/LifetimeComponent.h"
#include "../components/AIComponent.h"

class GameManagerSystem
{
public:
    void Update(std::vector<GameEvent>& gameEvents, std::vector<Entity>& entities, GameData& gameData, GameStateType& gameState)
    {
        for(auto& gameEvent : gameEvents)
        {
            switch (gameEvent.type)
            {
            case GameEventType::EnemyKilled:
            {
                Entity explosion;
                auto* enemyKilledPos = gameEvent.entity.GetComponent<TransformComponent>();
                Texture2D deathTexture = LoadTexture("textures/enemyDeath.png");
                explosion.AddComponent<RenderComponent>(deathTexture);
                explosion.AddComponent<LifetimeComponent>(0.2);
                explosion.AddComponent<TransformComponent>(enemyKilledPos->position.x, enemyKilledPos->position.y);
                entities.push_back(explosion);

                auto* ai = gameEvent.entity.GetComponent<AIComponent>();
                gameData.score+=ai->scoreWhenKilled;
                gameData.nDeadEnemies++;
                if(gameData.score>gameData.highScore)
                    gameData.highScore = gameData.score;

                break;
            }

            case GameEventType::PlayerHit:
            {
                //Check health
                auto* playerHealth = gameEvent.entity.GetComponent<HealthComponent>();
                if (!playerHealth)
                    return;

                playerHealth->currentHealth--;
                gameData.playerHealth = playerHealth->currentHealth;
                if (playerHealth->currentHealth < 1)
                {
                    gameEvent.entity.isActive = false;
                    gameState = GameStateType::GameOver;
                }
                break;
            }

            case GameEventType::WallHit:
            {
                Entity hit;
                auto* hitPos = gameEvent.entity.GetComponent<TransformComponent>();
                Texture2D hitTexture = LoadTexture("textures/bulletHit.png");
                hit.AddComponent<RenderComponent>(hitTexture);
                hit.AddComponent<LifetimeComponent>(0.1);
                hit.AddComponent<TransformComponent>(hitPos->position.x, hitPos->position.y);
                entities.push_back(hit);
                break;
            }

            default:
                break;
            }

        }
        gameEvents.clear();
    }

    void GetExplosion()
    {
        
    }
    
private:
    
};