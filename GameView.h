#ifndef SEMESTRALKA_GAMEVIEW_H
#define SEMESTRALKA_GAMEVIEW_H

#include "Game.h"

/**
 * @class GameView
 * @brief Represents the graphical view of the Tower of Hanoi game.
 *
 * The GameView class is responsible for rendering the Tower of Hanoi game
 * using SDL (Simple DirectMedia Layer). It provides methods for rendering
 * the towers, disks, and UI elements, as well as handling user input.
 *
 * This class depends on the Game and Disk classes to retrieve information
 * about the game state and disk properties.
 */
class GameView {
private:
    Game &game;
    SDL_Window *window;
    SDL_Renderer *renderer;

    std::vector<SDL_Rect> buttons;
    SDL_Texture *restartTextTexture;
    SDL_Texture *solveTextTexture;
    SDL_Texture *increaseTextTexture;
    SDL_Texture *decreaseTextTexture;
    SDL_Texture *exitTextTexture;
    SDL_Rect *movesDisplayRect;
    SDL_Texture *arrowUpTexture;
    SDL_Texture *arrowDownTexture;

    bool startButtonVisible; // Flag to track the visibility of the START button
    SDL_Texture *startTextTexture;
public:
    bool isDiskGrabbed = false;
    int grabbedTower = -1; // Tower index of the grabbed disk
    int grabbedDiskIndex = -1; // Index of the grabbed disk in its tower

    enum ButtonType {
        RESTART, SOLVE, INCREASE_DISKS, DECREASE_DISKS,EXIT , NUM_BUTTONS, START
    };

    GameView(Game &game);

    ~GameView();

    /**
    * @brief Render the game view.
    *
    * This method is responsible for rendering the Tower of Hanoi game view using SDL. It clears the renderer, sets the
    * draw color, and renders the various game elements based on the game state.
    */
    void render();

    SDL_Rect calculateDiskRect(const Disk &disk, int towerIndex);

    SDL_Rect calculateTowerRect(int towerIndex);

    void initializeButtons();

    ButtonType getButtonClicked(int x, int y);

    void renderButtons();

    int getTowerClicked(int x, int y);

    std::pair<int, int> getDiskClicked(int x, int y);

    /**
    * @brief Render the text and UI elements for the Tower of Hanoi game view.
    *
    * This method is responsible for rendering the moves count, disks count, and game won message on the game view.
    * It uses the renderText() method to render the text on the SDL renderer at the specified position.
    */
    void renderTextAndUI();

    void fillRectWithGradient(SDL_Renderer *renderer, SDL_Rect *rect, SDL_Color startColor, SDL_Color endColor);

    /**
    * @brief Render the specified text with the given color to the provided position on the SDL renderer.
    *
    * This function loads a font file and uses it to render the specified text with the given color on the provided position
    * of the SDL renderer. It creates a surface with the rendered text and then converts it to a texture to be rendered on
     * the screen. After rendering the text, the resources used for rendering are cleaned up.
     *
     * @param renderer The SDL renderer on which to render the text.
     * @param text The text to render.
    * @param textColor The color of the text.
    * @param position The position on the renderer where the text should be rendered.
    */
    void renderText(SDL_Renderer *renderer, const char *text, SDL_Color textColor, SDL_Rect position);

    void renderTowers();

    void renderDisks();

    void renderTowerBase();

    void initialize();

    /**
    * @class GameView
    * @brief Represents the graphical view of the Tower of Hanoi game.
    *
    * The GameView class is responsible for rendering the Tower of Hanoi game
    *  using SDL (Simple DirectMedia Layer). It provides methods for rendering
    * the towers, disks, and UI elements, as well as handling user input.
     *
    * This class depends on the Game and Disk classes to retrieve information
    * about the game state and disk properties.
    */
    void renderStartScreen();

    bool getClickedStart(int i, int i1);

    SDL_Rect calculateDiskRectAtMouse(const Disk &disk, int xM, int yM);


    void renderDiskWhenGrabbed();

    void animateDiskMovement(int i);

    void animateDiskMovement(int fromTower, int toTower);


    void renderDiskOnMove(Disk &disk, int posX, int posY);

    std::pair<int, int> calculateDiskRectXY(const Disk &disk, int towerIndex, int i);

    SDL_Rect calculateTowerRectDroppable(int towerIndex);

    void initializeTTF();

    void initializeWindowAndRenderer();

    void initializeSDL();
};


#endif //SEMESTRALKA_GAMEVIEW_H
