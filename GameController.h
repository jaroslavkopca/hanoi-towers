//
// Created by jarek on 11.01.2024.
//

#ifndef SEMESTRALKA_GAMECONTROLLER_H
#define SEMESTRALKA_GAMECONTROLLER_H

#include "Game.h"
#include "GameView.h"

class GameController {
private:
    Game& game;
    GameView& gameView;

    // Additional attributes for user input and game state
    bool isRunning;
    int selectedDisk;
    int selectedTower;

public:
    GameController(Game& game, GameView& view);
    void run();

    // Methods for handling user inputs and game controls
    void moveDisk(int fromTower, int toTower);
    void changeNumberOfDisks(int newNumber);
    void restartGame();
    void solveGame();
    void dragDisk(int diskId, int targetTower);

    void handleUserInput(SDL_Event &e);
};

#endif //SEMESTRALKA_GAMECONTROLLER_H
