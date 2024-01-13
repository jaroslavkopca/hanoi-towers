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
    SDL_Texture *exitTextTexture;
    SDL_Rect *movesDisplayRect;
    SDL_Texture *arrowUpTexture;
    SDL_Texture *arrowDownTexture;

    bool startButtonVisible; // Flag to track the visibility of the START button
    SDL_Texture *startTextTexture;





public:
    bool isDiskGrabbed = false;
    int grabbedTower = -1; // Tower index of the grabbed disk
    int grabbedDiskIndex = -1; // Index of the grabbed disk in its tower

    enum ButtonType {
        RESTART, SOLVE, INCREASE_DISKS, DECREASE_DISKS,EXIT , NUM_BUTTONS, START
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

    SDL_Rect calculateDiskRectAtMouse(const Disk &disk, int xM, int yM);


    void renderDiskWhenGrabbed();

    void animateDiskMovement(int i);

    void animateDiskMovement(int fromTower, int toTower);


    void renderDiskOnMove(Disk &disk, int posX, int posY);

    std::pair<int, int> calculateDiskRectXY(const Disk &disk, int towerIndex, int i);

    SDL_Rect calculateTowerRectDroppable(int towerIndex);
};


#endif //SEMESTRALKA_GAMEVIEW_H
