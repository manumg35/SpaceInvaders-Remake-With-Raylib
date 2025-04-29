#pragma once
#include "../ECS.h"
struct ColliderComponent : public Component
{
    ColliderComponent(float x, float y, float width, float height, float paddR, float paddBot) 
        : rect({x, y, width, height}), paddingRight(paddR), paddingBottom(paddBot) {};
    Rectangle rect;
    float paddingRight;
    float paddingBottom;
};