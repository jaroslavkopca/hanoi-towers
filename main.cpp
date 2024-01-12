#include <iostream>
#include "Game.cpp"
#include "GameView.h"


int main(int argc, char* argv[]) {
    Game game;
    GameView view(game);

    // Main loop (simplified)
    bool running = true;
    while (running) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Render game
        view.render();
        std::cout << "Jsme tu" << std::endl;
        game.startGame();
    }

    return 0;
}
