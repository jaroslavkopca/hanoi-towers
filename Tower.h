//d
// Created by jarek on 11.01.2024.
//

#ifndef SEMESTRALKA_TOWER_H
#define SEMESTRALKA_TOWER_H
#include "Disk.h"
#include "stack"

/**
 * @class Tower
 * A class representing a tower in a tower of hanoi puzzle.
 */
class Tower {
private:
    std::stack<Disk> disks;
public:
    Tower();
    bool addDisk(const Disk& disc);
    Disk peekDisk() const;
    Disk removeDisk();
    int getNumberOfDisks() const;
    bool isEmpty() const;
    std::stack<Disk> getDisks() const;


    const Disk &getTop();
};


#endif //SEMESTRALKA_TOWER_H
