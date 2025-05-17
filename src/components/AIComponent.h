#pragma once
#include "../ECS.h"
#include "../types/EntityTypes.h"

struct AIComponent : public Component
{
    AIComponent(int score, EnemyType type) : scoreWhenKilled(score), enemyType(type){}
    int scoreWhenKilled;
    EnemyType enemyType;
    float currentSpeed{1.f};
    inline static float freezedTimer{ 0.f };
    float freezeTime{ 0.25 };
    int xDir{1};
    bool isActive{ true };
    inline static bool freeze{ false };
};
