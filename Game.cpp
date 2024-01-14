#include "Game.h"
#include "Disk.h"
#include "Tower.h"


Game::Game() { setNumberOfDisks(3); }

void Game::moveDisc(int fromTower, int toTower) {
    Disk disc = towers[fromTower].removeDisk();
    towers[toTower].addDisk(disc);
}

bool Game::isGameWon() const {
    return towers[2].getNumberOfDisks() == numberOfDisc;
}

bool Game::isValidMove(int fromTower, int toTower) const {
    // Check if the move is valid (e.g., no disk is moved onto a smaller disk)
    if (fromTower < 0 || fromTower > 2 || toTower < 0 || toTower > 2 || fromTower == toTower) {
        return false;
    }

    if (towers[fromTower].isEmpty()) {
        return false;
    }

    if (!towers[toTower].isEmpty() &&
        towers[toTower].peekDisk().getSize() < towers[fromTower].peekDisk().getSize()) {
        return false;
    }

    return true;
}


int Game::getDiskPositionInTower(const Disk &targetDisk, int towerIndex) {
    const std::stack<Disk> &towerStack = towers[towerIndex].getDisks();
    std::stack<Disk> tempStack = towerStack; // Copy the tower's stack

    int position = towers[towerIndex].getNumberOfDisks();
    while (!tempStack.empty()) {
        const Disk &currentDisk = tempStack.top();
        if (currentDisk == targetDisk) {
            return position;
        }
        tempStack.pop();
        position--;
    }

    return -1; // Return -1 if the disk is not found in the tower

}


const int Game::getLargestDiskSize() {
    largestDiskSize = numberOfDisc * 10;
    return largestDiskSize;
}


void Game::setNumberOfDisks(int numberOfDisks) {
    if (numberOfDisks >= 1 && numberOfDisks <= 7) {
        // Clear existing towers and initialize with the new number of disks
        towers.clear();
        towers.resize(3);

        // Create and add the disks to the first tower based on the new number of disks
        for (int size = numberOfDisks; size > 0; --size) {
            SDL_Color diskColor = predefinedColors[size];
            towers[0].addDisk(Disk(size * 10, diskColor));
        }

        // Update the number of disks
        numberOfDisc = numberOfDisks;
    }
}

Disk Game::removeDisk(int i) {
    Disk disc = towers[i].removeDisk();
    return disc;
}

void Game::startGame() { isStarted = true; }

bool Game::isGameStarted() { return isStarted; }

void Game::resetGame() { setNumberOfDisks(numberOfDisc); }

const std::vector<Tower> &Game::getTowers() const { return towers; }

int const Game::getNumberOfMoves() { return (1 << numberOfDisc) - 1; }

const int Game::getNumberOfDisks() { return numberOfDisc; }

void Game::returnDisk(int i, Disk disk) { towers[i].addDisk(disk); }

bool Game::isSolvingGame() { return isSolving; }

void Game::setSolving(bool b) { isSolving = b; }


