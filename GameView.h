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

    std::vector<SDL_Rect> buttons;
    SDL_Texture* restartTextTexture;
    SDL_Texture* solveTextTexture;

public:
    enum ButtonType { RESTART, SOLVE, NUM_BUTTONS };
    GameView(Game &game);
    ~GameView();
    void render();
    SDL_Rect calculateDiskRect(const Disk& disk, int towerIndex);
    SDL_Rect calculateTowerRect(int towerIndex);

    void initializeButtons();
    ButtonType getButtonClicked(int x, int y);
    void renderButtons();

    int getTowerClicked(int x, int y);

    std::pair<int, int> getDiskClicked(int x, int y);
};


#endif //SEMESTRALKA_GAMEVIEW_H
