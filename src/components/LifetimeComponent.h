#pragma once
#include "../ECS.h"

struct LifetimeComponent : public Component
{
    LifetimeComponent(float timeToLive) : lifeTime(timeToLive) {} 

    float lifeTime;
    float elapsedTime{};
};