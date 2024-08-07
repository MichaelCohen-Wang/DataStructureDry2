#ifndef PIRATE_H_
#define PIRATE_H_

class Pirate {
public:
    int id;
    int fleetId;
    int salary;
    int rank;

    Pirate(int pirateId = 0, int fleetId = 0, int rank = 0) : id(pirateId), fleetId(fleetId), salary(0), rank(rank) {}
};

#endif // PIRATE_H_
