//
// Created by jarek on 11.01.2024.
//

#include "GameController.h"
#include <SDL.h>


GameController::GameController(Game &game, GameView &view)
        : game(game), gameView(view), isRunning(true), selectedDisk(-1), selectedTower(-1) {}

void GameController::run() {
    SDL_Event e;
    while (isRunning) {
        while (SDL_PollEvent(&e) != 0) {
            // Check for quit event
            if (e.type == SDL_QUIT) {
                isRunning = false;
            }

            // Additional event handling
            handleUserInput(e);
        }

        gameView.render(); // Render the game state
    }
}

void GameController::handleUserInput(SDL_Event &e) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && !gameView.isDiskGrabbed) {
        // Check if a disk was clicked
        auto [clickedTower, clickedDisk] = gameView.getDiskClicked(x, y);
        if (clickedDisk != -1) {
            gameView.isDiskGrabbed = true;
            gameView.grabbedTower = clickedTower;
            gameView.grabbedDiskIndex = clickedDisk;
            std::cout << "Disk grabbed: " << gameView.grabbedDiskIndex << std::endl;
            std::cout << "Tower first  :  " << gameView.grabbedTower << std::endl;
        }
    }

//    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && gameView.isDiskGrabbed) {
//        gameView.renderDiskWhenGrabbed();
//    }

    if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT && gameView.isDiskGrabbed) {
        // Check if a tower was clicked
        int towerIndex = gameView.getTowerClicked(x, y);
        if (towerIndex != -1) {
            std::cout << "Attempting to move disk  :  " << towerIndex << std::endl;
            if (towerIndex != gameView.grabbedTower && moveDisk(gameView.grabbedTower, towerIndex)) {
                std::cout << "Disk moved successfully" << std::endl;
            } else {
                std::cout << "Invalid move" << std::endl;
            }
        }
        gameView.isDiskGrabbed = false;
        gameView.grabbedTower = -1;
        gameView.grabbedDiskIndex = -1;
    }


    if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (gameView.getClickedStart(x, y)) {
            game.startGame();
        };
        GameView::ButtonType clickedButton = gameView.getButtonClicked(x, y);
        if (clickedButton != GameView::NUM_BUTTONS) {
            switch (clickedButton) {
                case GameView::RESTART:
                    restartGame();
                    std::cout << "RESTAAAAAAAAAAAART" << std::endl;
                    break;
                case GameView::SOLVE:
                    if (!game.isGameWon()) {
                        solveGame(game.getNumberOfDisks(), 0, 2, 1);
                    }
                    std::cout << "SOLVEEEEEEEEEEEEEEEEEE" << std::endl;
                    break;
                case GameView::INCREASE_DISKS:
                    game.setNumberOfDisks(game.getNumberOfDisks() + 1);
                    std::cout << "INCR" << std::endl;
                    break;
                case GameView::DECREASE_DISKS:
                    game.setNumberOfDisks(game.getNumberOfDisks() - 1);
                    std::cout << "DECR" << std::endl;
                    break;
            }
        }
    }
}


bool GameController::moveDisk(int fromTower, int toTower) {
    // Implement the logic to move a disk from one tower to another
    if (game.isValidMove(fromTower, toTower)) {
        game.moveDisc(fromTower, toTower);
        return true;
    }
    return false;
}


void GameController::restartGame() {
    game.resetGame();
}

void GameController::solveGame(int numberOfDisks, int sourceTower, int destinationTower, int auxiliaryTower) {
    if (numberOfDisks == 1) {
        // Base case: Move the smallest disk from source to destination
        game.moveDisc(sourceTower, destinationTower);
        gameView.render();
        SDL_Delay(400);
    } else {
        // Recursive case: Move (numberOfDisks-1) disks from source to auxiliary using destination as auxiliary
        solveGame(numberOfDisks - 1, sourceTower, auxiliaryTower, destinationTower);

        // Move the largest disk from source to destination
        game.moveDisc(sourceTower, destinationTower);
        gameView.render();
        SDL_Delay(400);

        // Move (numberOfDisks-1) disks from auxiliary to destination using source as auxiliary
        solveGame(numberOfDisks - 1, auxiliaryTower, destinationTower, sourceTower);
    }
}


void GameController::dragDisk(int diskId, int targetTower) {
    // Implement logic for dragging a disk to a new tower
    // This will likely involve game and view updates
}

Disk GameController::removeDisk(int tower) {
    game.removeDisk(tower);
}

void GameController::returnDisk(int tower, Disk disk) {
    game.returnDisk(tower,disk);
}
