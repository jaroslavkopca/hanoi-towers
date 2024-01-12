//
// Created by jarek on 11.01.2024.
//

#ifndef SEMESTRALKA_GAMEVIEW_H
#define SEMESTRALKA_GAMEVIEW_H

#include "Game.h"

class GameView {
private:
    Game &game;
    SDL_Window* window;
    SDL_Renderer* renderer;
public:
    GameView(Game &game);
    ~GameView();
    void render();
    SDL_Rect calculateDiskRect(const Disk& disk, int towerIndex);
    SDL_Rect calculateTowerRect(int towerIndex);
};


#endif //SEMESTRALKA_GAMEVIEW_H
