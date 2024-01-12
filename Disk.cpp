//
// Created by jarek on 11.01.2024.
//

#include "Disk.h"

Disk::Disk(int size, SDL_Color color) : size(size), color(color) {}

int Disk::getSize() const {
    return size;
}

SDL_Color Disk::getColor() const {
    return color;
}

bool Disk::operator==(const Disk& other) const {
    // Compare the attributes of 'this' Disk and 'other' Disk
    return size == other.size; // Adjust the comparison based on your criteria
}