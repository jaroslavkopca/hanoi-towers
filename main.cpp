#include "Game.cpp"
#include "GameView.h"
#include "GameController.h"



int main(int argc, char* argv[]) {
    std::ofstream logFile("logfile.txt", std::ios::app);
    std::cout.rdbuf(logFile.rdbuf());
    std::cerr.rdbuf(logFile.rdbuf());
    Game game;
    GameView view(game);
    GameController gameController(game,view);
    std::cout << "Zacatek" << std::endl;
    // Main loop (simplified)
    bool running = true;
    while (running) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            gameController.handleUserInput(event);
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        view.render();

        // Render game
//        std::cout << "Jsme tu" << std::endl;
//        game.startGame();
    }

    return 0;
}
