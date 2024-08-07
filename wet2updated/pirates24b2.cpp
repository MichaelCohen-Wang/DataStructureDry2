#include "pirates24b2.h"
#include <iostream>
oceans_t::oceans_t() {}

oceans_t::~oceans_t() {}

StatusType oceans_t::add_fleet(int fleetId) {
    if (fleetId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (fleets.find(fleetId) != nullptr) {
        return StatusType::FAILURE;
    }
    try {
        fleets.insert(fleetId, Fleet(fleetId));
    } catch (...) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType oceans_t::add_pirate(int pirateId, int fleetId) {
    if (pirateId <= 0 || fleetId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (pirates.find(pirateId) != nullptr || fleets.find(fleetId) == nullptr) {
        return StatusType::FAILURE;
    }
    try {
        Fleet* fleet = fleets.find(fleetId);
        if (!fleet) return StatusType::FAILURE;
        int rank = fleet->pirates.get_size() + 1;
        Pirate pirate(pirateId, fleetId, rank);
        pirates.insert(pirateId, pirate);
        fleet->pirates.push_back(pirate);
    } catch (...) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType oceans_t::pay_pirate(int pirateId, int salary) {
    if (pirateId <= 0 || salary <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Pirate* pirate = pirates.find(pirateId);
    if (pirate == nullptr) {
        return StatusType::FAILURE;
    }
    pirate->salary += salary;
    return StatusType::SUCCESS;
}

output_t<int> oceans_t::num_ships_for_fleet(int fleetId) {
    if (fleetId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    Fleet* fleet = fleets.find(fleetId);
    if (fleet == nullptr) {
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>(fleet->ships);
}

output_t<int> oceans_t::get_pirate_money(int pirateId) {
    if (pirateId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    Pirate* pirate = pirates.find(pirateId);
    if (pirate == nullptr) {
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>(pirate->salary);
}

StatusType oceans_t::unite_fleets(int fleetId1, int fleetId2) {
    if (fleetId1 <= 0 || fleetId2 <= 0 || fleetId1 == fleetId2) {
        return StatusType::INVALID_INPUT;
    }

    if (!fleets.unite(fleetId1, fleetId2)) {
        return StatusType::FAILURE;
    }

    Fleet* fleet1 = fleets.find(fleetId1);
    Fleet* fleet2 = fleets.find(fleetId2);

    if (fleet1 == nullptr || fleet2 == nullptr) {
        return StatusType::FAILURE;
    }

    Fleet* larger = (fleet1->pirates.get_size() >= fleet2->pirates.get_size()) ? fleet1 : fleet2;
    Fleet* smaller = (larger == fleet1) ? fleet2 : fleet1;

    larger->ships += smaller->ships;
    for (int i = 0; i < smaller->pirates.get_size(); ++i) {
        Pirate& pirate = smaller->pirates[i];
        pirate.fleetId = larger->id;
        pirate.rank += larger->pirates.get_size();
        larger->pirates.push_back(pirate);
        pirates.insert(pirate.id, pirate);
    }

    fleets.remove(smaller->id);
    return StatusType::SUCCESS;
}

StatusType oceans_t::pirate_argument(int pirateId1, int pirateId2) {
    if (pirateId1 <= 0 || pirateId2 <= 0 || pirateId1 == pirateId2) {
        return StatusType::INVALID_INPUT;
    }
    Pirate* pirate1 = pirates.find(pirateId1);
    Pirate* pirate2 = pirates.find(pirateId2);
    if (pirate1 == nullptr || pirate2 == nullptr) {
        //std::cout<< "failed at nullptr"<< std::endl; 
        return StatusType::FAILURE;
    }

    if (pirate1->fleetId != pirate2->fleetId) {
        //std::cout<< "failed at !="<< std::endl; 
        return StatusType::FAILURE;
    }

    int rankDiff = abs(pirate1->rank - pirate2->rank);
    if (pirate1->rank > pirate2->rank) {
        pirate1->salary -= rankDiff;
        pirate2->salary += rankDiff;
    } else {
        pirate2->salary -= rankDiff;
        pirate1->salary += rankDiff;
    }

    return StatusType::SUCCESS;
}
