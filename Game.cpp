#include "Game.h"
#include <iostream>
#include "Disk.h"
#include "Tower.h"
#include "GameView.h"





Game::Game(){
    // Initialize the game, for example, by asking the number of disks
//    std::cout << "Enter the number of disks: ";
//    std::cin >> numberOfDisk;
    towers.resize(3);

    towers[0].addDisk(Disk(40, SDL_Color{255, 0, 0})); // Red disk
    towers[0].addDisk(Disk(30, SDL_Color{0, 255, 0})); // Green disk
    towers[0].addDisk(Disk(20, SDL_Color{0, 0, 255})); // Blue disk
}

void Game::startGame() {
//    bool gameOver = false;
//
//    SDL_Event e;
//    while (!gameOver) {
//        while (SDL_PollEvent(&e) != 0) {
//            // Check for quit event
//            if (e.type == SDL_QUIT) {
//                gameOver = true;
//            }
//
//            // Handle other events like mouse clicks
//            if (e.type == SDL_MOUSEBUTTONDOWN) {
//                // Determine which tower or disk was clicked
//                // This method depends on how you've implemented your GameView
////                int clickedTower = gameView.getTowerClicked(e.button.x, e.button.y);
//
//                // If a tower is clicked, determine the move
//                if (clickedTower != -1) {
//                    // Logic to determine fromTower and toTower based on user's click
//                    int fromTower, toTower;
//                    // ... Your logic to set fromTower and toTower based on click ...
//
//                    if (isValidMove(fromTower, toTower)) {
//                        moveDisc(fromTower, toTower);
//
//                        if (isGameWon()) {
//                            std::cout << "Congratulations! You won!" << std::endl;
//                            gameOver = true;
//                        }
//                    } else {
//                        std::cout << "Invalid move. Try again." << std::endl;
//                    }
//                }
//            }
//        }
//
//        // Render game state
////        gameView.render();
//    }
}


//void Game::startGame(int argc, char *argv[]) {
//
//}

void Game::moveDisc(int fromTower, int toTower) {
    // Assuming tower indices are 1-based in user input and 0-based internally
    Disk disc = towers[fromTower].removeDisk();
    towers[toTower].addDisk(disc);
}

bool Game::isGameWon() const {
    // Game is won if all disks are on the last tower
    return towers[2].getNumberOfDisks() == numberOfDisc;
}

bool Game::isValidMove(int fromTower, int toTower) const {
    // Check if the move is valid (e.g., no disk is moved onto a smaller disk)
    if (fromTower < 0 || fromTower > 2 || toTower < 0 || toTower > 2 || fromTower == toTower) {
        return false;
    }

    if (towers[fromTower ].isEmpty()) {
        return false;
    }

    if (!towers[toTower ].isEmpty() &&
        towers[toTower].peekDisk().getSize() < towers[fromTower].peekDisk().getSize()) {
        return false;
    }

    return true;
}

const std::vector<Tower>& Game::getTowers() const {
    return towers;
}

int Game::getDiskPositionInTower(const Disk& targetDisk, int towerIndex) {
    const std::stack<Disk>& towerStack = towers[towerIndex].getDisks();
    std::stack<Disk> tempStack = towerStack; // Copy the tower's stack

    int position = towers[towerIndex].getNumberOfDisks();
    while (!tempStack.empty()) {
        const Disk& currentDisk = tempStack.top();
        if (currentDisk == targetDisk) {
            return position;
        }
        tempStack.pop();
        position--;
    }

    return -1; // Return -1 if the disk is not found in the tower
}

void Game::setupGame(int i) {


}

void Game::resetGame() {

}

