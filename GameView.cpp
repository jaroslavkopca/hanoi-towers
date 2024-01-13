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

// Initialize towers and disks
void GameView::renderTowers() {
    // Render towers with a more aesthetic look
    for (int i = 0; i < game.getTowers().size(); ++i) {
        SDL_Rect towerRect = calculateTowerRect(i);
        fillRectWithGradient(renderer, &towerRect, SDL_Color{50, 50, 50, 255}, SDL_Color{100, 100, 100, 255});
    }
}

// Render the base of the towers
void GameView::renderTowerBase() {
    for (int i = 0; i < game.getTowers().size(); ++i) {
        SDL_Rect towerRect = calculateTowerRect(i);
        int largestDiskSize = game.getLargestDiskSize() + 10;

        int baseWidth = largestDiskSize * 250 * 0.01; // Adjust this factor to control the base size
        SDL_Rect baseRect = {towerRect.x - (baseWidth - towerRect.w) / 2, towerRect.y + towerRect.h, baseWidth, 20};
        fillRectWithGradient(renderer, &baseRect, SDL_Color{50, 50, 50, 255}, SDL_Color{100, 100, 100, 255});
    }
}

void GameView::renderDisks() {
    // Render disks on the towers
    for (int i = 0; i < game.getTowers().size(); ++i) {
        const auto &tower = game.getTowers()[i];
        int diskCount = tower.getNumberOfDisks();
        if (diskCount > 0) {
            for (int j = diskCount - 1; j >= 0; --j) {
                Disk disk = tower.getDiskAt(j);
                SDL_Color diskColor = disk.getColor();
                SDL_Rect diskRect = calculateDiskRect(disk, i); // Positioning based on tower index

                // Ensure that the disk size is valid and greater than zero
                if (diskRect.w > 0 && diskRect.h > 0) {
                    fillRectWithGradient(renderer, &diskRect, diskColor, SDL_Color{static_cast<Uint8>(diskColor.r / 2),
                                                                                   static_cast<Uint8>(diskColor.g / 2),
                                                                                   static_cast<Uint8>(diskColor.b / 2),
                                                                                   255});
                }
            }
        }
    }
}


void GameView::render() {
    if (renderer) {
        // Set a darker background color
        if (SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255) < 0) {
            // handle error
        }
        if (SDL_RenderClear(renderer) < 0) {
            // handle error
        }


        if (!game.isGameStarted()) {
            renderStartScreen();
        } else {
            initializeButtons();
            renderTowers();
            renderTowerBase();
            renderTextAndUI();
            renderButtons();
            renderDisks();
        }

        // Present the updated renderer
        SDL_RenderPresent(renderer);
    }
}


void GameView::renderText(SDL_Renderer *renderer, const char *text, SDL_Color textColor, SDL_Rect position) {
    // Load a font (you should do this initialization elsewhere)
    TTF_Font *font = TTF_OpenFont("fonts/Pixellettersfull.ttf", 24);
    if (font == nullptr) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }

    // Create a surface with the text and color
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (textSurface == nullptr) {
        std::cerr << "Failed to create text surface! TTF_Error: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    // Create a texture from the surface
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        std::cerr << "Failed to create text texture! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    // Clean up the surface and font
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    // Render the text texture to the specified position
    SDL_RenderCopy(renderer, textTexture, nullptr, &position);

    // Clean up the texture
    SDL_DestroyTexture(textTexture);
}


void GameView::renderTextAndUI() {
    SDL_Color textColor = {200, 200, 200}; // Light grey for visibility against the dark background

    // Render the moves count
    std::string movesText = "Moves: " + std::to_string(game.getNumberOfMoves());
    renderText(renderer, movesText.c_str(), textColor, {10, 550, 100, 30}); // Position text at the bottom left corner

    std::string disksText = "Disks: " + std::to_string(game.getNumberOfDisks());
    renderText(renderer, disksText.c_str(), textColor, {10, 10, 100, 30}); // Position text at the bottom left corner
}


void GameView::renderStartScreen() {
    SDL_Init(TTF_Init());
    // Clear the renderer
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Create a "Start" button
    SDL_Rect startButtonRect = {200, 200, 400, 200}; // Position and size of the button
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Button color
    SDL_RenderFillRect(renderer, &startButtonRect);
    fillRectWithGradient(renderer,&startButtonRect,SDL_Color{50, 50, 50, 255}, SDL_Color{100, 100, 100, 255});

    // Render text for the "Start" button
    SDL_Color textColor = {255, 255, 255};
    renderText(renderer, "Start", textColor, {260, 260, 300, 100}); // Position and size of the text

    // Present the renderer
    SDL_RenderPresent(renderer);
}


// Utility function to fill a rectangle with a gradient
void GameView::fillRectWithGradient(SDL_Renderer *renderer, SDL_Rect *rect, SDL_Color startColor, SDL_Color endColor) {
    // Starting color values
    int r = startColor.r;
    int g = startColor.g;
    int b = startColor.b;
    int a = startColor.a;

    // Color change per step
    int rStep = (endColor.r - startColor.r) / rect->h;
    int gStep = (endColor.g - startColor.g) / rect->h;
    int bStep = (endColor.b - startColor.b) / rect->h;
    int aStep = (endColor.a - startColor.a) / rect->h;

    // Iterate over the height of the rectangle to create the gradient
    for (int i = 0; i < rect->h; i++) {
        // Set the color for the current line
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        // Draw the line
        SDL_RenderDrawLine(renderer, rect->x, rect->y + i, rect->x + rect->w, rect->y + i);
        // Adjust the color for the next line
        r += rStep;
        g += gStep;
        b += bStep;
        a += aStep;
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
        const auto &tower = game.getTowers()[i];
        int diskCount = tower.getNumberOfDisks();

        // Iterate from top disk to bottom disk
        for (int j = diskCount - 1; j >= 0; --j) {
            Disk towerAtInt = tower.getDiskAt(j);
            Disk diskattop = tower.getDisks().top();
            diskattop.getColor();
            SDL_Rect diskRect = calculateDiskRect(diskattop, i);

//            std::cout << "Checking Disk " << j << " in Tower " << i << ": Rect("
//                      << diskRect.x << ", " << diskRect.y << ", "
//                      << diskRect.w << ", " << diskRect.h << ") against Click("
//                      << x << ", " << y << ")\n";

            if (x >= diskRect.x && x < (diskRect.x + diskRect.w) &&
                y >= diskRect.y && y < (diskRect.y + diskRect.h)) {

                return {i, j};
            }
        }
    }
//    std::cout << "No disk clicked" << std::endl;
    return {-1, -1}; // No disk clicked
}


void GameView::initializeButtons() {
    int buttonWidth = 100;
    int buttonHeight = 50;
    int yPos = 10; // Position at the top of the window
    int xPos = 1200 / 2 - (buttonWidth * NUM_BUTTONS) / 2; // Center buttons horizontally

    // Initialize button rectangles
    buttons.resize(NUM_BUTTONS);
    buttons[RESTART] = {xPos, yPos, buttonWidth, buttonHeight}; // Restart button
    buttons[SOLVE] = {xPos + buttonWidth + 10, yPos, buttonWidth, buttonHeight}; // Solve button
    buttons[INCREASE_DISKS] = {xPos - buttonWidth - 10, yPos, buttonWidth, buttonHeight}; // Up button
    buttons[DECREASE_DISKS] = {xPos - buttonWidth*2 - 20, yPos, buttonWidth, buttonHeight}; // Down button

    SDL_Init(TTF_Init());
    // Initialize SDL_ttf for text rendering
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
    }

    // Load font
    TTF_Font *font = TTF_OpenFont("fonts/Pixellettersfull.ttf", 24);
    if (font == nullptr) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
    }

    // Set text color as white
    SDL_Color textColor = {255, 255, 255};

    // Create surfaces for button text
    SDL_Surface *restartSurface = TTF_RenderText_Solid(font, "Restart", textColor);
    SDL_Surface *solveSurface = TTF_RenderText_Solid(font, "Solve", textColor);
    SDL_Surface *increaseSurface = TTF_RenderText_Solid(font, "Up", textColor);
    SDL_Surface *decreaseSurface = TTF_RenderText_Solid(font, "Down", textColor);

    // Create textures from surfaces
    restartTextTexture = SDL_CreateTextureFromSurface(renderer, restartSurface);
    solveTextTexture = SDL_CreateTextureFromSurface(renderer, solveSurface);
    increaseTextTexture = SDL_CreateTextureFromSurface(renderer, increaseSurface);
    decreaseTextTexture = SDL_CreateTextureFromSurface(renderer, decreaseSurface);

    // Clean up surfaces
    SDL_FreeSurface(restartSurface);
    SDL_FreeSurface(solveSurface);
    SDL_FreeSurface(increaseSurface);
    SDL_FreeSurface(decreaseSurface);

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
        SDL_Texture *textTexture;
        // Render text texture on the button
        switch (i) {
            case RESTART:
                textTexture = restartTextTexture;
                break;
            case SOLVE:
                textTexture = solveTextTexture;
                break;
            case INCREASE_DISKS:
                textTexture = increaseTextTexture;
                break;
            case DECREASE_DISKS:
                textTexture = decreaseTextTexture;
                break;
        }
        int textWidth, textHeight;
        SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
        SDL_Rect textRect = {buttons[i].x + (buttons[i].w - textWidth) / 2,
                             buttons[i].y + (buttons[i].h - textHeight) / 2, textWidth, textHeight};
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    }
}

GameView::ButtonType GameView::getButtonClicked(int x, int y) {
    for (size_t i = 0; i < buttons.size(); ++i) {
        // Check if the click coordinates are within the button's rectangle
        if (x >= buttons[i].x && x < (buttons[i].x + buttons[i].w) &&
            y >= buttons[i].y && y < (buttons[i].y + buttons[i].h)) {
            return static_cast<ButtonType>(i); // Update the currently clicked button
        }
    }

    return NUM_BUTTONS; // No button clicked
}

SDL_Rect GameView::calculateTowerRect(int towerIndex) {
    int towerWidth = 20; // Width of the tower
    int towerHeight = (20 * (game.getNumberOfDisks() + 1)); // Height of the tower
    int windowWidth = 800; // Assuming window width is 800
    int windowHeight = 600; // Assuming window height is 600
    int spacing = (windowWidth > 4) ? (windowWidth / 4) : 1; // Increase the spacing to divide window into 6 parts for 3 towers
    int baseHeight = 20; // Height of the base

    int x;
    if  (towerIndex == 0){
        x =  ((spacing) * (towerIndex + 1) - towerWidth / 2) - 10;
    }else if(towerIndex == 2 ){
        x = ((spacing) * (towerIndex + 1) - towerWidth / 2) +10;
    }else{
        x = (spacing) * (towerIndex + 1) - towerWidth / 2;
    }

    int y = 400 - towerHeight - baseHeight; // Adjusted 'y' for the base

    SDL_Rect towerRect = {x, y, towerWidth, towerHeight};
    return towerRect;
}

SDL_Rect GameView::calculateDiskRect(const Disk &disk, int towerIndex) {
    int diskHeight = 20; // Height of each disk
    int baseDiskWidth = 250; // Base width to be modified based on disk size
    int diskWidth = baseDiskWidth * 0.01 * disk.getSize(); // Example size calculation

    int diskPosition = game.getDiskPositionInTower(disk, towerIndex);

    // Reuse tower rectangle to position disks
    SDL_Rect towerRect = calculateTowerRect(towerIndex);
    int x = towerRect.x + (towerRect.w - diskWidth) / 2; // Center disk on tower
    int y = towerRect.y + towerRect.h - diskHeight * (diskPosition);

    SDL_Rect diskRect = {x, y, diskWidth, diskHeight};
    return diskRect;
}

bool GameView::getClickedStart(int i, int i1) {
    int mouseX, mouseY;
    SDL_Rect startButtonRect = {200, 200, 400, 200}; // Position and size of the button
    SDL_GetMouseState(&mouseX, &mouseY);

    // Check if the mouse click is within the "Start" button
    if (mouseX >= startButtonRect.x && mouseX < (startButtonRect.x + startButtonRect.w) &&
        mouseY >= startButtonRect.y && mouseY < (startButtonRect.y + startButtonRect.h)) {
        return true;
    }
    return false;
}

