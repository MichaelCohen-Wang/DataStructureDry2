#ifndef PIRATE_H_
#define PIRATE_H_

class Pirate {
private:
    int pirateId;
    int fleetId;
    int rank;
    int money;

public:
    Pirate(int id, int fleet, int rank);
    void add_money(int amount);
    int get_money() const;
    int get_fleet_id() const;
    int get_rank() const;
    void receive_payment(int amount);
    void pay(int amount);
    void set_fleet_id(int fleet);
    void set_rank(int new_rank);
};

Pirate::Pirate(int id, int fleet, int rank) : pirateId(id), fleetId(fleet), rank(rank), money(0) {}

void Pirate::add_money(int amount) {
    money += amount;
}

int Pirate::get_money() const {
    return money;
}

int Pirate::get_fleet_id() const {
    return fleetId;
}

int Pirate::get_rank() const {
    return rank;
}

void Pirate::receive_payment(int amount) {
    money += amount;
}

void Pirate::pay(int amount) {
    money -= amount;
}

void Pirate::set_fleet_id(int fleet) {
    fleetId = fleet;
}

void Pirate::set_rank(int new_rank) {
    rank = new_rank;
}

#endif // PIRATE_H_
