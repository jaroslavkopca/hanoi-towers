//
// Created by jarek on 11.01.2024.
//

#ifndef SEMESTRALKA_GAME_H
#define SEMESTRALKA_GAME_H

#include "Tower.h"
#include "vector"
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

public:
    explicit  Game();

    void startGame();

    void moveDisc(int fromTower, int toTower);

    bool isValidMove(int fromTower, int toTower) const;


    bool isGameWon() const;

    std::vector<Tower> getTowers();


    int getDiskPositionInTower(const Disk &disk, int i);
};


#endif //SEMESTRALKA_GAME_H
