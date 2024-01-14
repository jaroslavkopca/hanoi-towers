#ifndef SEMESTRALKA_TOWER_H
#define SEMESTRALKA_TOWER_H

#include "Disk.h"



/**
 * @class Tower
 *
 * @brief Represents a tower in a tower of Hanoi game.
 *
 * The Tower class represents a tower in a tower of Hanoi game. It provides
 * methods to add disks, remove disks, and access the top disk and number
 * of disks in the tower.
 */
class Tower {
private:
    std::stack<Disk> disks;
public:
    Tower();

    /**
     * @fn bool Tower::addDisk(const Disk& disc)
     * @brief Adds a disk to the tower.
     *
     * This function adds a disk to the tower if the tower is empty or if the size
     * of the top disk is greater than the size of the disk being added. If the
     * disk is added, the function returns true. If the disk cannot be added,
     * the function returns false.
     *
     * @param disc The disk to be added.
     * @return True if the disk was added, false otherwise.
     */
    bool addDisk(const Disk &disc);

    /**
     * @brief Returns a reference to the stack of disks in the tower.
     *
     * This function returns a reference to a constant stack that contains the disks
     * in the tower. The function is marked as const, indicating that it does not modify
     * the state of the tower.
     *
     * @return A reference to a constant stack of disks.
     */
    const std::stack<Disk> &getDisks() const;

    Disk peekDisk() const;

    Disk removeDisk();

    int getNumberOfDisks() const;

    bool isEmpty() const;

    const Disk &getTop() const;

};


#endif //SEMESTRALKA_TOWER_H
