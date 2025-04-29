#pragma once
#include "../ECS.h"


struct HealthComponent : public Component
{
    HealthComponent(int health): currentHealth(health){};
    int currentHealth{};
};