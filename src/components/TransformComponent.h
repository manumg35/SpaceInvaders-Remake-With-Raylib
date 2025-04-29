#pragma once
#include "../ECS.h"

struct TransformComponent : public Component
{
    TransformComponent(float x, float y) : position{x, y} {};
    Vector2 position;
};