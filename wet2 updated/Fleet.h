#ifndef FLEET_H_
#define FLEET_H_

#include "DynamicArray.h"
#include "Pirate.h"

class Fleet {
public:
    int id;
    int ships;
    DynamicArray<Pirate> pirates;

    Fleet(int fleetId) : id(fleetId), ships(1) {}
};

#endif // FLEET_H_
