#pragma once
#include "../ECS.h"
#include "../components/TransformComponent.h"
#include "../components/RenderComponent.h"

class RenderSystem 
{
public:
    void Render(std::vector<Entity>& entities) {
        for (auto& entity : entities) {
            if(!entity.isActive)
                continue;
            auto* pos = entity.GetComponent<TransformComponent>();
            auto* render = entity.GetComponent<RenderComponent>();
            if (pos && render)
                DrawTexture(render->texture, pos->position.x, pos->position.y, render->textureTint);
        }
    }
};