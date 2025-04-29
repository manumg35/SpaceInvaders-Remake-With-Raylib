#pragma once
#include "../ECS.h"

struct BulletComponent : public Component
{
    BulletComponent() = default;
    bool isActive{};
};