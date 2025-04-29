#pragma once
#include "../ECS.h"

struct AnimationComponent : public Component
{
    AnimationComponent(Texture2D text[2], float frameDur ) : frameDuration(frameDur)
    {
        textures[0] = text[0];
        textures[1] = text[1];
    } 

    Texture2D textures[2];
    float frameDuration{0.5};
    float timer{0.f};
    int frameCount{2};
    int currentFrame{};
};