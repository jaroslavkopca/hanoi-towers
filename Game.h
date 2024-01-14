#ifndef SEMESTRALKA_GAME_H
#define SEMESTRALKA_GAME_H

#include "Tower.h"

/**
 * @class Game
 *
 * @brief Represents a Tower of Hanoi game.
 *
 * The Game class represents a Tower of Hanoi game. It provides methods to
 * move disks between towers, check if the game is won, validate moves,
 * and access information about the game state.
 */
class Game {
private:
    std::vector<Tower> towers;
    int numberOfDisc;
    bool isStarted;
    int largestDiskSize = 0;
    bool isSolving = false;

public:
    const SDL_Color predefinedColors[7] = {
            {255, 0,   0},
            {0,   255, 0},
            {0,   0,   255},
            {255, 255, 0},
            {255, 0,   255},
            {0,   255, 255},
            {255, 165, 0}
    };

    /**
     * @fn explicit Game::Game();
     * @brief Constructs a Game object.
     *
     * Constructs a Game object initializing the necessary member variables.
     */
    explicit Game();

    /**
     * @fn void Game::moveDisc(int fromTower, int toTower)
     * @brief Moves a disk from one tower to another.
     *
     * This method moves a disk from the tower specified by fromTower to
     * the tower specified by toTower.
     *
     * @param fromTower The index of the tower to move the disk from.
     * @param toTower The index of the tower to move the disk to.
     */
    void moveDisc(int fromTower, int toTower);

    /**
     * @fn bool Game::isGameWon() const
     * @brief Returns true if the game is won, false otherwise.
     *
     * Determines if the game is won by checking whether all disks
     * are on the final tower.
     */
    bool isGameWon() const;

    /**
     * @fn bool Game::isValidMove(int fromTower, int toTower) const
     * @brief Checks if a move is valid.
     *
     * This method checks if a disk can be moved from the tower specified by
     * fromTower to the tower specified by toTower according to the rules of
     * the game.
     *
     * @param fromTower The index of the tower to move the disk from.
     * @param toTower The index of the tower to move the disk to.
     */
    bool isValidMove(int fromTower, int toTower) const;

    /**
     * @fn int Game::getDiskPositionInTower(const Disk &disk, int i)
     * @brief Returns the position of a disk in a tower.
     *
     * @param disk The disk to locate
     * @param i The tower to check
     */
    int getDiskPositionInTower(const Disk &disk, int i);

    /**
     * @fn void Game::setNumberOfDisks(int i)
     * @brief Sets the number of disks to i.
     *
     * @param i The total number of disks in the game.
     */
    void setNumberOfDisks(int i);

    /**
     * @fn const int Game::getLargestDiskSize()
     * @brief Returns the size of the largest disk.
     */
    const int getLargestDiskSize();

    /**
     * @fn Disk Game::removeDisk(int i)
     * @brief Removes and returns the top disk from tower i.
     *
     * @param i The tower index.
     */
    Disk removeDisk(int i);

    /**
     * @fn void Game::startGame()
     * @brief Starts the game.
     */
    void startGame();

    /**
     * @fn bool Game::isGameStarted()
     * @brief Returns true if the game has started, false otherwise.
     */
    bool isGameStarted();

    /**
     * @fn void Game::resetGame()
     * @brief Resets the game.
     */
    void resetGame();

    /**
     * @fn const std::vector<Tower> &Game::getTowers() const
     * @brief Returns a const reference to the vector of towers.
     */
    const std::vector<Tower> &getTowers() const;

    /**
     * @fn const int Game::getNumberOfMoves()
     * @brief Returns the number of moves made in the game.
     */
    const int getNumberOfMoves();

    /**
     * @fn const int Game::getNumberOfDisks()
     * @brief Returns the total number of disks in the game.
     */
    const int getNumberOfDisks();

    /**
     * @fn void Game::returnDisk(int i, Disk disk)
     * @brief Places a disk back on top of tower i.
     *
     * @param i The tower index.
     * @param disk The disk to place.
     */
    void returnDisk(int i, Disk disk);

    /**
     * @fn bool Game::isSolvingGame()
     * @brief Returns true if the game is in the process of being solved, false otherwise.
     */
    bool isSolvingGame();

    /**
     * @fn void Game::setSolving(bool b)
     * @brief Sets the solving status of the game.
     *
     * @param b The solving status to set.
     */
    void setSolving(bool b);
};


#endif //SEMESTRALKA_GAME_H