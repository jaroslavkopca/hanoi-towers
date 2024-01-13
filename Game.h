//
// Created by jarek on 11.01.2024.
//

#ifndef SEMESTRALKA_GAME_H
#define SEMESTRALKA_GAME_H


#include "Tower.h"



/**
 * @class Game
 * @brief Represents the game of Tower of Hanoi.
 *
 * The Game class manages the state of the Tower of Hanoi game.
 * It keeps track of the towers and the number of disks in the game.
 */
class Game {
private:
    std::vector<Tower> towers;
    int numberOfDisc;
    bool isStarted;
    int largestDiskSize = 0;

public:
    explicit  Game();

    const SDL_Color predefinedColors[7] = {
            {255, 0, 0},
            {0, 255, 0},
            {0, 0, 255},
            {255, 255, 0},
            {255, 0, 255},
            {0, 255, 255},
            {255, 165, 0}
    };



    void moveDisc(int fromTower, int toTower);

    bool isValidMove(int fromTower, int toTower) const;


    bool isGameWon() const;

    const std::vector<Tower>& getTowers() const;


    int getDiskPositionInTower(const Disk &disk, int i);

    void startGame();


    void resetGame();

    int getNumberOfMoves();

    int getLargestDiskSize();

    bool isGameStarted();

    int getNumberOfDisks();

    void setNumberOfDisks(int i);

    Disk removeDisk(int i);

    void returnDisk(int i, Disk disk);
};


#endif //SEMESTRALKA_GAME_H
