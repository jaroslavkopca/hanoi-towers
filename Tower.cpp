#include "Tower.h"

Tower::Tower() {}

bool Tower::addDisk(const Disk &disc) {
    //Check if the stack is empty or the size of the top disc is greater than the disc to be added.
    if (disks.empty() || disks.top().getSize() > disc.getSize()) {
        disks.push(disc);
        return true;
    }
    return false;  // If the top disc is not greater than the one to be added, return false
}

const Disk &Tower::getDiskAt(int i) const {
    std::stack<Disk> tempStack = disks;

    if (i >= 0 && i < tempStack.size()) {
        for (int j = 0; j < i; ++j) {
            tempStack.pop();
        }
    }
    return tempStack.top();
}

Disk Tower::removeDisk() {
    Disk disk = disks.top();
    disks.pop();
    return disk;
}

Disk Tower::peekDisk() const { return disks.top(); }

int Tower::getNumberOfDisks() const { return disks.size(); }

bool Tower::isEmpty() const { return disks.empty(); }

const std::stack<Disk> &Tower::getDisks() const { return disks; }

const Disk &Tower::getTop() const { return disks.top(); }


