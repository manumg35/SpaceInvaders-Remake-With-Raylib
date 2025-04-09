#pragma once
#include "raylib.h"
#include "ECS.h"

enum class EntityType
{
    None,
    Player,
    Enemy,
    Wall,
    EnemyBullet,
    PlayerBullet
};

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

struct RenderComponent : public Component
{
    RenderComponent(Texture2D text, Color tint = WHITE) : texture(text), textureTint(tint) {};
    Texture2D texture;
    Color textureTint;
};

struct ColliderComponent : public Component
{
    ColliderComponent(float x, float y, float width, float height, float paddR, float paddBot) 
        : rect({x, y, width, height}), paddingRight(paddR), paddingBottom(paddBot) {};
    Rectangle rect;
    float paddingRight;
    float paddingBottom;
};

struct AIComponent : public Component
{
    AIComponent() = default;
    static inline int xDir{1};
    static inline float currentSpeed{1.f};    
};

struct BulletComponent : public Component
{
    BulletComponent() = default;
    bool isActive{};
};

struct TagComponent : public Component
{
    TagComponent(EntityType entType = EntityType::None) : type(entType){}

    EntityType type;
};
