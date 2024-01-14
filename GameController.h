#ifndef SEMESTRALKA_GAMECONTROLLER_H
#define SEMESTRALKA_GAMECONTROLLER_H

#include "Game.h"
#include "GameView.h"

/**
 * @class GameController
 *
 * @brief Controls the interaction between the Game model and the GameView.
 *
 * The GameController class handles user inputs and game controls. It serves as
 * a bridge between the Game model and the GameView, ensuring that any user inputs
 * are properly processed and updating the game state accordingly.
 */
class GameController {
private:
    Game &game;
    GameView &gameView;

public:

    GameController(Game &game, GameView &view);

    void run();

    // Methods for handling user inputs and game controls
    bool moveDisk(int fromTower, int toTower);

    void changeNumberOfDisks(int newNumber);

    void restartGame();


    void dragDisk(int diskId, int targetTower);

    /**
    * @brief Handles user input events.
    *
    * This function is responsible for handling user input events such as mouse clicks and button presses.
    * It performs different actions based on the event type and the current state of the game.
    *
    * @param e - The SDL_Event object containing the user input event.
    */
    void handleUserInput(SDL_Event &e);

    /**
    * @fn void GameController::solveGame(int numberOfDisks, int sourceTower, int destinationTower, int auxiliaryTower)
    * @brief Solves the game using the Tower of Hanoi algorithm.
    *
    * This function solves the game using the Tower of Hanoi algorithm recursively. It moves the specified number of disks from
    * the source tower to the destination tower using the auxiliary tower as an intermediate step. It animates the disk movements
    * and updates the game state after each move.
    *
    * @param numberOfDisks - The number of disks to be moved.
    * @param sourceTower - The tower from which the disks will be moved.
    * @param destinationTower - The tower to which the disks will be moved.
    * @param auxiliaryTower - The auxiliary tower used in the moving process.
    *
    * @return None.
    *
    * @note This function assumes that the game is in "solving" state, which can be checked using the `isSolvingGame()` method of the `Game` class.
    * If the game is not in the "solving" state, this function will return without performing any action.
    */
    void solveGame(int numberOfDisks, int sourceTower, int destinationTower, int auxiliaryTower);

    Disk removeDisk(int tower);

    void returnDisk(int tower, Disk disk);

    void animateDiskMovement(int fromTower, int toTower);

};

#endif //SEMESTRALKA_GAMECONTROLLER_H
