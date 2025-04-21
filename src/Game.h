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

    //SYSTEMS
    PlayerControlSystem pcSystem;
    InputSystem inputSystem;
    MovementSystem movementSystem;
    AISystem aiSystem;
    ColliderSystem colliderSystem;
    BulletSystem bulletSystem;
    RenderSystem renderSystem;

    std::vector<Entity> entities;
    std::vector<ShootEvent> shootEvents;

    std::shared_ptr<Entity> player = nullptr;

    int maxScore{0};
    int currentScore{0};
    int screenWidth{400};
    int screenHeight{600};
    int targetFPS{60};

};