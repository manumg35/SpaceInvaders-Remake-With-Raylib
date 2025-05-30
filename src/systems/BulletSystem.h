#pragma once 
#include "../ECS.h"
#include "../components/TransformComponent.h"
#include "../components/MovementComponent.h"
#include "../components/TagComponent.h"
#include "../components/BulletComponent.h"
#include "../events/ShootEvent.h"

class BulletSystem
{
public:

    void Update(std::vector<Entity>& entities, std::vector<ShootEvent>& shootEvents)
    {
        //check if should spawn new bullets
        for(auto& shootEv: shootEvents)
        {
            for(auto& bullet: entities)
            {
                if(bullet.isActive)
                    continue;

                auto* bulComp = bullet.GetComponent<BulletComponent>();
                auto* tag = bullet.GetComponent<TagComponent>();

                if(!bulComp || tag->type != shootEv.bulletType)
                    continue;

                auto* bulPos = bullet.GetComponent<TransformComponent>();
                auto* bulMov = bullet.GetComponent<MovementComponent>();

                bullet.isActive = true;
                
                bulPos->position = shootEv.position;           
                bulMov->velocity.y = shootEv.ySpeed * shootEv.yDirection;
                
                break;
            }
        }
        shootEvents.clear();

        //check if bullet should be active
        /*for (auto& bullet : entities) {

            if (!bullet.isActive)
                continue;

            auto* bulPos = bullet.GetComponent<TransformComponent>();
            auto* bulComp = bullet.GetComponent<BulletComponent>();
            auto* bulMov = bullet.GetComponent<MovementComponent>();

            if(!bulComp || !bulPos || !bulMov)
                continue;
            
            if(bulPos->position.y < -50 || bulPos->position.y > 600)
            {
                bullet.isActive = false;
                bulMov->velocity.y = 0;

            }
        }*/

    }
};
