#pragma once
#include "../ECS.h"
#include "../types/EntityTypes.h"

struct TagComponent : public Component
{
    TagComponent(EntityType entType = EntityType::None) : type(entType){}

    EntityType type;
};