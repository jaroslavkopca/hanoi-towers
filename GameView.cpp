//
// Created by jarek on 11.01.2024.
//

#include "GameView.h"
#include <SDL.h>
#include "iostream"
#include <SDL_ttf.h>

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
    if (restartTextTexture) SDL_DestroyTexture(restartTextTexture);
    if (solveTextTexture) SDL_DestroyTexture(solveTextTexture);
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
        initializeButtons();
        renderButtons();


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
            for(int j = diskCount - 1; j >= 0; --j) {
                Disk disk = tower.getDiskAt(j);
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

int GameView::getTowerClicked(int x, int y) {
    for (int i = 0; i < game.getTowers().size(); ++i) {
        SDL_Rect towerRect = calculateTowerRect(i);
        if (x >= towerRect.x && x < (towerRect.x + towerRect.w) &&
            y >= towerRect.y && y < (towerRect.y + towerRect.h)) {
            return i;
        }
    }
    return -1; // No tower clicked
}

std::pair<int, int> GameView::getDiskClicked(int x, int y) {
    for (int i = 0; i < game.getTowers().size(); ++i) {
        const auto& tower = game.getTowers()[i];
        int diskCount = tower.getNumberOfDisks();

        // Iterate from top disk to bottom disk
        for (int j = diskCount - 1; j >= 0; --j) {
            Disk towerAtInt =  tower.getDiskAt(j);
            Disk diskattop = tower.getDisks().top();
            diskattop.getColor();
            SDL_Rect diskRect = calculateDiskRect(diskattop, i);

            std::cout << "Checking Disk " << j << " in Tower " << i << ": Rect("
                      << diskRect.x << ", " << diskRect.y << ", "
                      << diskRect.w << ", " << diskRect.h << ") against Click("
                      << x << ", " << y << ")\n";

            if (x >= diskRect.x && x < (diskRect.x + diskRect.w) &&
                y >= diskRect.y && y < (diskRect.y + diskRect.h)) {

//                game.getDiskPositionInTower(Tower().getDiskAt(j))
                return {i, j};
            }
        }
    }
    std::cout << "No disk clicked" << std::endl;
    return {-1, -1}; // No disk clicked
}


void GameView::initializeButtons() {
    int buttonWidth = 100;
    int buttonHeight = 50;
    int yPos = 10; // Position at the top of the window
    int xPos = 800 / 2 - (buttonWidth * NUM_BUTTONS) / 2; // Center buttons horizontally

    // Initialize button rectangles
    buttons.resize(NUM_BUTTONS);
    buttons[RESTART] = {xPos, yPos, buttonWidth, buttonHeight}; // Restart button
    buttons[SOLVE] = {xPos + buttonWidth + 10, yPos, buttonWidth, buttonHeight}; // Solve button

    // Initialize SDL_ttf for text rendering
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
    }

    // Load font
    TTF_Font* font = TTF_OpenFont("fonts/Pixellettersfull.ttf", 24);
    if (font == nullptr) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
    }

    // Set text color as white
    SDL_Color textColor = {255, 255, 255};

    // Create surfaces for button text
    SDL_Surface* restartSurface = TTF_RenderText_Solid(font, "Restart", textColor);
    SDL_Surface* solveSurface = TTF_RenderText_Solid(font, "Solve", textColor);

    // Create textures from surfaces
    restartTextTexture = SDL_CreateTextureFromSurface(renderer, restartSurface);
    solveTextTexture = SDL_CreateTextureFromSurface(renderer, solveSurface);

    // Clean up surfaces
    SDL_FreeSurface(restartSurface);
    SDL_FreeSurface(solveSurface);

    // Close the font after use
    TTF_CloseFont(font);
}

void GameView::renderButtons() {
    for (size_t i = 0; i < buttons.size(); ++i) {
        // Draw button rectangle
        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255); // Darker button color
        SDL_RenderFillRect(renderer, &buttons[i]);

        // Draw button border for a "button-like" appearance
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Light grey for the border
        SDL_RenderDrawRect(renderer, &buttons[i]);

        // Render text texture on the button
        SDL_Texture* textTexture = (i == RESTART) ? restartTextTexture : solveTextTexture;
        int textWidth, textHeight;
        SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
        SDL_Rect textRect = {buttons[i].x + (buttons[i].w - textWidth) / 2, buttons[i].y + (buttons[i].h - textHeight) / 2, textWidth, textHeight};
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    }
}

GameView::ButtonType GameView::getButtonClicked(int x, int y) {
    for (size_t i = 0; i < buttons.size(); ++i) {
        // Draw button rectangle
        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255); // Darker button color
        SDL_RenderFillRect(renderer, &buttons[i]);

        // Draw button border for a "button-like" appearance
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Light grey for the border
        SDL_RenderDrawRect(renderer, &buttons[i]);

        // Render text texture on the button
        SDL_Texture* textTexture = (i == RESTART) ? restartTextTexture : solveTextTexture;
        int textWidth, textHeight;
        SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
        SDL_Rect textRect = {buttons[i].x + (buttons[i].w - textWidth) / 2, buttons[i].y + (buttons[i].h - textHeight) / 2, textWidth, textHeight};
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    }
    return NUM_BUTTONS;
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
    int baseDiskWidth = 250; // Base width to be modified based on disk size
    int diskWidth = baseDiskWidth * 0.01 *disk.getSize(); // Example size calculation

    int diskPosition = game.getDiskPositionInTower(disk, towerIndex);

    // Reuse tower rectangle to position disks
    SDL_Rect towerRect = calculateTowerRect(towerIndex);
    int x = towerRect.x + (towerRect.w - diskWidth) / 2; // Center disk on tower
    int y = towerRect.y + towerRect.h - diskHeight * (diskPosition + 1);

    SDL_Rect diskRect = {x, y, diskWidth, diskHeight};
    return diskRect;
}