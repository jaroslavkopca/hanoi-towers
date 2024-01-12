//
// Created by jarek on 11.01.2024.
//

#ifndef SEMESTRALKA_DISK_H
#define SEMESTRALKA_DISK_H

#include <SDL.h>
#include <vector>
#include <stack>

/**
 * @class Disk
 *
 * @brief The Disk class represents a disc in a disc-based game.
 *
 * The Disk class provides functionalities to create a disc with a specified size and to retrieve its size.
 */
class Disk {
private:
    int size;
    SDL_Color color;
public:
    Disk(int size, SDL_Color color);

    int getSize() const;

    SDL_Color getColor() const;

    bool operator==(const Disk& other) const;


};


#endif //SEMESTRALKA_DISK_H
