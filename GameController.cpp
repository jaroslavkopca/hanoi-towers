//
// Created by jarek on 11.01.2024.
//

#include "GameController.h"
#include <SDL.h>

GameController::GameController(Game& game, GameView& view)
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

void GameController::handleUserInput(SDL_Event& e) {
    // Handle keyboard events
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_r: // Restart game
                restartGame();
                break;
                // Add other keybindings as needed
        }
    }

    // Handle mouse events for disk dragging (as an example)
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        // Example: Get mouse click coordinates and process for disk selection
        int x, y;
        SDL_GetMouseState(&x, &y);
        // Logic to determine if a disk is selected
        // selectedDisk = determineSelectedDisk(x, y);
    }
}

void GameController::moveDisk(int fromTower, int toTower) {
    // Implement the logic to move a disk from one tower to another
    if (game.isValidMove(fromTower, toTower)) {
        game.moveDisc(fromTower, toTower);
    }
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
