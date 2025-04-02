#pragma once
#include "raylib.h"
#include "ECS.h"

struct TransformComponent : public Component
{
    TransformComponent(float x, float y) : position{x, y} {};
    Vector2 position;
};

struct MovementComponent : public Component
{
    MovementComponent(float x, float y) : velocity{x, y} {};
    Vector2 velocity;
};

struct SpriteComponent : public Component
{
    SpriteComponent(Texture2D text) : texture(text) {};
    Texture2D texture;
};

struct RectColliderComponent : public Component
{
    RectColliderComponent(float x, float y, float width, float height) : rect({x, y, width, height}) {};
    Rectangle rect;
};
