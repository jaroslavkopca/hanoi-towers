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
public:
    GameController(Game& game, GameView& view);
    void run();
};


#endif //SEMESTRALKA_GAMECONTROLLER_H
