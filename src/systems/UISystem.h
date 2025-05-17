#pragma once
#include "../core/GameData.h"
#include "../core/GameState.h"
#include "raylib.h"

class UISystem
{
public:
    void Render(GameData& gameData, GameStateType gameState)
    {
        
        switch (gameState)
        {
        case GameStateType::Paused:
            DrawText("Press the space bar to start", 25, 450, 20, WHITE);
            DrawText(TextFormat("Hi-Score: %i", gameData.highScore), 25, 400, 20, WHITE);
            break;
        case GameStateType::GameOver:
            DrawText("Press the space bar to restart", 25, 450, 20, WHITE);
            DrawText("You lost! :c", 25, 425, 20, WHITE);
            DrawText(TextFormat("Your score: %i", gameData.score), 25, 400, 20, WHITE);
            DrawText(TextFormat("Hi-Score: %i", gameData.highScore), 25, 375, 20, WHITE);
            break;
        case GameStateType::NewWave:
            DrawText("Press the space bar to start new wave", 25, 450, 20, WHITE);
            DrawText("You killed all space invaders!", 25, 425, 20, WHITE);
            DrawText(TextFormat("Your score: %i", gameData.score), 25, 400, 20, WHITE);
            DrawText(TextFormat("Hi-Score: %i", gameData.highScore), 25, 375, 20, WHITE);
            break;
        default:1
            DrawText(TextFormat("Lives: %i", gameData.playerHealth), 10, 575, 20, WHITE);
            DrawText(TextFormat("Score: %i", gameData.score), 10, 10, 20, WHITE);
            DrawText(TextFormat("Hi-Score: %i", gameData.highScore), 10, 30, 20, WHITE);
            break;
        }
    }

};