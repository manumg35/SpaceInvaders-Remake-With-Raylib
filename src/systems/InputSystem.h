#pragma once
#include <vector>
#include "../core/PlayerCommand.h"
#include "raylib.h"

class InputSystem
{
public:
    std::vector<PlayerCommand> HandleInput()
    {
        std::vector<PlayerCommand> commands;

        if(IsKeyDown(KEY_D))
            commands.push_back(PlayerCommand::MoveRight);
        else if(IsKeyDown(KEY_A))
            commands.push_back(PlayerCommand::MoveLeft);
        else
            commands.push_back(PlayerCommand::Stop);

        if(IsKeyPressed(KEY_SPACE))
            commands.push_back(PlayerCommand::Shoot);
        
        return commands;
    }
};