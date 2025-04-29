#pragma once
#include "../ECS.h"
#include "../types/EntityTypes.h"

struct AIComponent : public Component
{
    AIComponent(int score, EnemyType type) : scoreWhenKilled(score), enemyType(type){}
    int scoreWhenKilled;
    EnemyType enemyType;
    float currentSpeed{1.f};
    int xDir{1};
    bool isActive{true};
};
