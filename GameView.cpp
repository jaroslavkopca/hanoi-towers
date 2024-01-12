//
// Created by jarek on 11.01.2024.
//

#include "GameView.h"
#include <SDL.h>
#include "iostream"

GameView::GameView(Game &game) : game(game) {
    // Initialize SDL and create window and renderer
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    } else {
        window = SDL_CreateWindow("Tower of Hanoi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
                                  SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (!renderer) {
                std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            }
        }
    }
}

GameView::~GameView() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

void GameView::render() {
    if (renderer) {
        if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255) < 0) { // White background
            // handle error
        }
        if (SDL_RenderClear(renderer) < 0) {
            // handle error
        }

        // Render towers
        for (int i = 0; i < game.getTowers().size(); ++i) {
            SDL_Rect towerRect = calculateTowerRect(i);
            if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) < 0) { // Black color for towers
                // handle error
            }
            if (SDL_RenderFillRect(renderer, &towerRect) < 0) {
                // handle error
            }
        }

        // Render disks
        for (int i = 0; i < game.getTowers().size(); ++i) {
            const auto& tower = game.getTowers()[i];

            int diskCount = tower.getNumberOfDisks();
            for(int j = 0; j < diskCount; ++j) {
                const Disk& disk = tower.getDiskAt(j);
                SDL_Rect diskRect = calculateDiskRect(disk, i); // Pass tower index for positioning
                if (SDL_SetRenderDrawColor(renderer, disk.getColor().r, disk.getColor().g, disk.getColor().b, 255) < 0) {
                    // handle error
                }
                if (SDL_RenderFillRect(renderer, &diskRect) < 0) {
                    // handle error
                }
            }
        }

        SDL_RenderPresent(renderer);
    }
}

// handle possible division by zero
SDL_Rect GameView::calculateTowerRect(int towerIndex) {
    int towerWidth = 20; // Width of the tower
    int towerHeight = 100; // Height of the tower
    int windowWidth = 800; // Assuming window width is 800
    int spacing = (windowWidth > 4) ? (windowWidth / 4) : 1; // Dividing window into 4 parts for 3 towers

    int x = spacing * (towerIndex + 1) - towerWidth / 2;
    int y = 600 - towerHeight; // Assuming window height is 600

    SDL_Rect towerRect = {x, y, towerWidth, towerHeight};
    return towerRect;
}

SDL_Rect GameView::calculateDiskRect(const Disk& disk, int towerIndex) {
    int diskHeight = 20; // Height of each disk
    int baseDiskWidth = 40; // Base width to be modified based on disk size
    int diskWidth = baseDiskWidth - 5 * disk.getSize(); // Example size calculation

    int diskPosition = game.getDiskPositionInTower(disk, towerIndex);

    // Reuse tower rectangle to position disks
    SDL_Rect towerRect = calculateTowerRect(towerIndex);
    int x = towerRect.x + (towerRect.w - diskWidth) / 2; // Center disk on tower
    int y = towerRect.y + towerRect.h - diskHeight * (diskPosition + 1);

    SDL_Rect diskRect = {x, y, diskWidth, diskHeight};
    return diskRect;
}