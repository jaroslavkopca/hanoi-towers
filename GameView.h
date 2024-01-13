//
// Created by jarek on 11.01.2024.
//

#ifndef SEMESTRALKA_GAMEVIEW_H
#define SEMESTRALKA_GAMEVIEW_H

#include "Game.h"

class GameView {
private:
    Game &game;
    SDL_Window *window;
    SDL_Renderer *renderer;

    std::vector<SDL_Rect> buttons;
    SDL_Texture *restartTextTexture;
    SDL_Texture *solveTextTexture;
    SDL_Texture *increaseTextTexture;
    SDL_Texture *decreaseTextTexture;
    SDL_Rect *movesDisplayRect;
    SDL_Texture *arrowUpTexture;
    SDL_Texture *arrowDownTexture;

    bool startButtonVisible; // Flag to track the visibility of the START button
    SDL_Texture *startTextTexture;


public:
    enum ButtonType {
        RESTART, SOLVE, INCREASE_DISKS, DECREASE_DISKS, NUM_BUTTONS, START
    };

    GameView(Game &game);

    ~GameView();

    void render();

    SDL_Rect calculateDiskRect(const Disk &disk, int towerIndex);

    SDL_Rect calculateTowerRect(int towerIndex);

    void initializeButtons();

    ButtonType getButtonClicked(int x, int y);

    void renderButtons();

    int getTowerClicked(int x, int y);

    std::pair<int, int> getDiskClicked(int x, int y);

    void renderTextAndUI();

    void fillRectWithGradient(SDL_Renderer *renderer, SDL_Rect *rect, SDL_Color startColor, SDL_Color endColor);

    void renderText(SDL_Renderer *renderer, const char *text, SDL_Color textColor, SDL_Rect position);

    void renderTowers();

    void renderDisks();

    void renderTowerBase();

    void initialize();

    void renderStartScreen();

    bool getClickedStart(int i, int i1);
};


#endif //SEMESTRALKA_GAMEVIEW_H
