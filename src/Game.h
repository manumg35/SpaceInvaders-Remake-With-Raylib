#pragma once
#include "Components.h"
#include "ECS.h"
#include "Systems.h"
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

    //TEXTURES
    Texture2D playerTexture;
    Texture2D playBulletTexture;
    Texture2D enemyTexture;
    Texture2D enemyBulletTexture;
    

    void Update();
    void Render();
    void Restart();
    void LoadTextures();
    void UnloadTextures();
    void CreateEntities();
};