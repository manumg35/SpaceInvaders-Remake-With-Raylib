#pragma once
#include "../ECS.h"
struct MovementComponent : public Component
{
    MovementComponent(float x, float y) : velocity{x, y} {};
    Vector2 velocity;
};
