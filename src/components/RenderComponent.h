#pragma once
#include "../ECS.h"
struct RenderComponent : public Component
{
    RenderComponent(Texture2D& text, Color tint = WHITE) : texture(text), textureTint(tint) {};
    Texture2D texture;
    Color textureTint;
};
