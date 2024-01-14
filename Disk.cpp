#include "Disk.h"

Disk::Disk(int size, SDL_Color color) : size(size), color(color) {}

int Disk::getSize() const { return size; }

SDL_Color Disk::getColor() const { return color; }

bool Disk::operator==(const Disk &other) const { return size == other.size; }