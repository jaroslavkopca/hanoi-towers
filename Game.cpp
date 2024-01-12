#include "Game.h"
#include <iostream>
#include "Disk.h"
#include "Tower.h"




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
//     Main game loop
//    while (!isGameWon()) {
        int from, to;
        std::cout << "Enter the tower to move from and to (e.g., 1 2): ";
        std::cin >> from >> to;

        if (isValidMove(from, to)) {
            moveDisc(from, to);
        } else {
            std::cout << "Invalid move. Try again." << std::endl;
        }
//    }

//    std::cout << "Congratulations! You have solved the Tower of Hanoi!" << std::endl;
}


//void Game::startGame(int argc, char *argv[]) {
//
//}

void Game::moveDisc(int fromTower, int toTower) {
    // Assuming tower indices are 1-based in user input and 0-based internally
    Disk disc = towers[fromTower - 1].removeDisk();
    towers[toTower - 1].addDisk(disc);
}

bool Game::isGameWon() const {
    // Game is won if all disks are on the last tower
    return towers[2].getNumberOfDisks() == numberOfDisc;
}

bool Game::isValidMove(int fromTower, int toTower) const {
    // Check if the move is valid (e.g., no disk is moved onto a smaller disk)
    if (fromTower < 1 || fromTower > 3 || toTower < 1 || toTower > 3 || fromTower == toTower) {
        return false;
    }

    if (towers[fromTower - 1].isEmpty()) {
        return false;
    }

    if (!towers[toTower - 1].isEmpty() &&
        towers[toTower - 1].peekDisk().getSize() < towers[fromTower - 1].peekDisk().getSize()) {
        return false;
    }

    return true;
}

std::vector<Tower> Game::getTowers(){
    return towers;
}

int Game::getDiskPositionInTower(const Disk& targetDisk, int towerIndex) {
    const std::stack<Disk>& towerStack = towers[towerIndex].getDisks();
    std::stack<Disk> tempStack = towerStack; // Copy the tower's stack

    int position = 0;
    while (!tempStack.empty()) {
        const Disk& currentDisk = tempStack.top();
        if (currentDisk == targetDisk) {
            return position;
        }
        tempStack.pop();
        position++;
    }

    return -1; // Return -1 if the disk is not found in the tower
}

