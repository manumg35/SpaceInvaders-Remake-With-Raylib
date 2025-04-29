#pragma once
#include "../ECS.h"
#include "../components/LifetimeComponent.h"

class LifeTimeSystem
{
public:
    void Update(std::vector<Entity>& entities, float deltaTime)
    {
        for(auto& entity : entities)
        {
            if(!entity.isActive)
            continue;
            
            auto* lifetime = entity.GetComponent<LifetimeComponent>();

            if(!lifetime)
                continue;

            lifetime->elapsedTime+=deltaTime;
            if(lifetime->elapsedTime > lifetime->lifeTime)
                entity.isActive = false;

        }
    }
};