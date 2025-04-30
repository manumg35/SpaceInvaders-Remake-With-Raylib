#include "../ECS.h"
#pragma once
enum class GameEventType
{
    PlayerHit,
    EnemyKilled,
    WallHit,
};

struct GameEvent
{
    GameEventType type;
    Entity entity;
};