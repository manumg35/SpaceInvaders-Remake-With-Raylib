#include "../ECS.h"
#pragma once
enum class GameEventType
{
    PlayerHit,
    EnemyKilled,
};

struct GameEvent
{
    GameEventType type;
    Entity entity;
};