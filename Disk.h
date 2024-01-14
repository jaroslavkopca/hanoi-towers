#ifndef SEMESTRALKA_DISK_H
#define SEMESTRALKA_DISK_H

#include <iostream>
#include <fstream>
#include <SDL.h>
#include <vector>
#include <stack>


/**
 * @class Disk
 *
 * @brief Represents a disk with a given size and color.
 *
 * The Disk class represents a disk with a specific size and color.
 * It provides methods to access the size and color of the disk,
 * as well as an equality operator to compare disks.
 */
class Disk {
private:
    int size;
    SDL_Color color;
public:
    /**
     * @brief Initializes a Disk with the specified size and color.
     *
     * The Disk constructor initializes a Disk object with the provided
     * size and color.
     *
     * @param size The size of the disk.
     * @param color The color of the disk.
     */
    Disk(int size, SDL_Color color);

    int getSize() const;

    SDL_Color getColor() const;

    /**
     * @fn bool Disk::operator==(const Disk& other) const
     * @brief Equality operator for comparing two Disk objects.
     *
     * This operator compares the size of two Disk objects and returns true if they are equal,
     * indicating that the disks have the same size. Otherwise, it returns false.
     *
     * @param other The Disk object to compare against.
     * @return True if the disks have the same size, false otherwise.
     */
    bool operator==(const Disk& other) const;


};


#endif //SEMESTRALKA_DISK_H
