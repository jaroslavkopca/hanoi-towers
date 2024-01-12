//
// Created by jarek on 11.01.2024.
//

#include "GameController.h"
#include <SDL.h>

enum class GameControllerState {
    SELECT_DISK,
    WAIT_FOR_TOWER
};

GameControllerState currentState = GameControllerState::SELECT_DISK;

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
    // ... Existing keyboard handling ...

    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        // Check if a button was clicked
        GameView::ButtonType clickedButton = gameView.getButtonClicked(x, y);
        if (clickedButton != GameView::NUM_BUTTONS) {
            switch (clickedButton) {
                case GameView::RESTART:
                    restartGame();
                    std::cout << "RESTAAAAAAAAAAAART" << std::endl;
                    break;
                case GameView::SOLVE:
                    solveGame();
                    std::cout << "SOLVEEEEEEEEEEEEEEEEEE" << std::endl;
                    break;
                    // Handle other buttons
            }
        } else {
            // Check if a disk was clicked
//            if (selectedDisk == -1) {
//                // If no disk is currently selected, check if a disk was clicked
//                auto [clickedTower, clickedDisk] = gameView.getDiskClicked(x, y);
//                if (clickedDisk != -1) {
//                    std::cout << "Disk selected"  << clickedDisk << std::endl;
//                    selectedDisk = clickedDisk;
//                    selectedTower = clickedTower;
//                    std::cout << "Selected tower"  <<selectedTower << std::endl;
//                }
//            } else {
//                // If a disk is already selected, check if a tower was clicked
//                int towerIndex = gameView.getTowerClicked(x, y);
//                if (towerIndex != -1) {
//                    std::cout << "Attempting to move disk" << std::endl;
//                    if (towerIndex != selectedTower && moveDisk(selectedTower, towerIndex)) {
//                        std::cout << "Disk moved successfully" << std::endl;
//                    } else {
//                        std::cout << "Invalid move" << std::endl;
//                    }
//                    // Reset selection regardless of move success
//                    selectedDisk = -1;
//                    selectedTower = -1;
//                }
//            }
            if (currentState == GameControllerState::SELECT_DISK) {
                // Check if a disk was clicked
                auto [clickedTower, clickedDisk] = gameView.getDiskClicked(x, y);
                if (clickedDisk != -1) {
                    std::cout << "Disk selected: " << clickedDisk << std::endl;
                    selectedDisk = clickedDisk;
                    selectedTower = clickedTower;
                    std::cout << "Tower first  :  " << selectedTower << std::endl;
                    currentState = GameControllerState::WAIT_FOR_TOWER;
                }
            } else if (currentState == GameControllerState::WAIT_FOR_TOWER) {
                // Check if a tower was clicked
                int towerIndex = gameView.getTowerClicked(x, y);
                if (towerIndex != -1) {
                    std::cout << "Attempting to move disk  :  " << towerIndex << std::endl;
                    if (towerIndex != selectedTower && moveDisk(selectedTower, towerIndex)) {
                        std::cout << "Disk moved successfully" << std::endl;
                    } else {
                        std::cout << "Invalid move" << std::endl;
                    }
                    currentState = GameControllerState::SELECT_DISK;
                }
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

void GameController::changeNumberOfDisks(int newNumber) {
    // Implement logic to change the number of disks in the game
    game.setupGame(newNumber); // Assuming setupGame method exists in Game
}

void GameController::restartGame() {
    // Implement game restart logic
    game.resetGame(); // Assuming resetGame method exists in Game
}

void GameController::solveGame() {
    // Implement logic to automatically solve the game
    // This could be an algorithm to solve Tower of Hanoi
}

void GameController::dragDisk(int diskId, int targetTower) {
    // Implement logic for dragging a disk to a new tower
    // This will likely involve game and view updates
}

// ... Other methods as needed
