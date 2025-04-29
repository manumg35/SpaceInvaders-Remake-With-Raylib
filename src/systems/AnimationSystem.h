#pragma once
#include "../ECS.h"
#include "../components/RenderComponent.h"
#include "../components/AnimationComponent.h"

class AnimationSystem
{
public:
    void UpdateAnimation(std::vector<Entity>& entities, float deltaTime)
    {
        for (auto& entity : entities) {
            if(!entity.isActive)
                continue;

            auto* anim = entity.GetComponent<AnimationComponent>();
            auto* render = entity.GetComponent<RenderComponent>();
            if (!anim || !render)
                continue;

            anim->timer+=deltaTime;
            if(anim->timer >= anim->frameDuration)
            {
                anim->timer = 0.f;
                anim->currentFrame++;
                if(anim->currentFrame == anim->frameCount)
                    anim->currentFrame = 0;
                render->texture = anim->textures[anim->currentFrame];
            }
            
        }
    }
};