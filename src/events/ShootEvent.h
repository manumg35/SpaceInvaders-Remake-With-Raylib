#pragma once
#include "raylib.h"
#include "../types/EntityTypes.h"

struct ShootEvent
{
    Vector2 position;
    float ySpeed;
    int yDirection;
    EntityType bulletType;
};