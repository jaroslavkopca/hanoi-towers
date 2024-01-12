#include <iostream>
#include <fstream>
#include "Game.cpp"
#include "GameView.h"



int main(int argc, char* argv[]) {

    std::clog << "Hello, World!" << std::endl;
    Game game;
    GameView view(game);
    std::cout << "Hello, World!" << std::endl;
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
//        std::cout << "Jsme tu" << std::endl;
        game.startGame();
    }

    return 0;
}
