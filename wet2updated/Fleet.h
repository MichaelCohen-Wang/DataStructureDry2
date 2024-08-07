#ifndef FLEET_H_
#define FLEET_H_

#include "DynamicArray.h"
#include "Pirate.h"
#include <memory>

class Fleet {
private:
    int fleetId;
    DynamicArray<std::unique_ptr<Pirate>> pirates;

public:
    Fleet(int id);
    ~Fleet();
    void add_pirate(std::unique_ptr<Pirate> pirate);
    void merge_with(Fleet* other);
    // Other fleet-related methods

    int getId() const;
    int getNumPirates() const;
    Pirate* getPirate(int index) const;
};

Fleet::Fleet(int id) : fleetId(id) {}

Fleet::~Fleet() {
    // No need to manually delete pirates since they are managed by unique_ptr
}

void Fleet::add_pirate(std::unique_ptr<Pirate> pirate) {
    pirates.push_back(std::move(pirate));
}

void Fleet::merge_with(Fleet* other) {
    for (int i = 0; i < other->pirates.get_size(); ++i) {
        other->pirates[i]->set_fleet_id(fleetId);
        other->pirates[i]->set_rank(pirates.get_size() + 1);
        pirates.push_back(std::move(other->pirates[i]));
    }
}

int Fleet::getId() const {
    return fleetId;
}

int Fleet::getNumPirates() const {
    return pirates.get_size();
}

Pirate* Fleet::getPirate(int index) const {
    return pirates[index].get();
}

#endif // FLEET_H_
