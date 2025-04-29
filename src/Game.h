#pragma once
#include "ECS.h"
#include "systems/AllSystems.h"
#include "raylib.h"
#include <memory>

class Game
{
public:
    void Init();
    void Run();
    void Close();
    

private:

    std::vector<Entity> entities;
    std::vector<ShootEvent> shootEvents;

    std::shared_ptr<Entity> player = nullptr;

    GameData gameData;

    int maxScore{0};
    int currentScore{0};
    int screenWidth{400};
    int screenHeight{600};
    int targetFPS{60};
    GameStateType gameState = GameStateType::Paused;

    //SYSTEMS
    PlayerControlSystem pcSystem;
    InputSystem inputSystem;
    MovementSystem movementSystem;
    AISystem aiSystem;
    ColliderSystem colliderSystem;
    BulletSystem bulletSystem;
    RenderSystem renderSystem;
    GameManagerSystem gameManager;
    UISystem uiSystem;
    AnimationSystem animationSystem;
    LifeTimeSystem lifeTimeSystem;

    //TEXTURES
    Texture2D playerTexture;
    Texture2D playBulletTexture;
    Texture2D normEnemyTextures[2];
    Texture2D coneEnemyTextures[2];
    Texture2D chunkyEnemyTextures[2];
    Texture2D enemyBulletTextures[2];
    

    void Update();
    void Render(bool renderJustUI = false);
    void Restart();
    void LoadTextures();
    void UnloadTextures();
    void CreateEntities();
};