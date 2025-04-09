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

private:

    //SYSTEMS
    RenderSystem renderSystem;
    InputSystem inputSystem;
    MovementSystem movementSystem;
    AISystem aiSystem;
    ColliderSystem colliderSystem;
    BulletSystem bulletSystem;
    PlayerControlSystem pcSystem;

    std::vector<Entity> entities;
    std::vector<ShootEvent> shootEvents;

    std::shared_ptr<Entity> player = nullptr;

    int screenWidth{400};
    int screenHeight{600};
    int targetFPS{60};

};