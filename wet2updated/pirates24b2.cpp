#include "pirates24b2.h"

oceans_t::oceans_t()
{
    // Initialization code
}

oceans_t::~oceans_t()
{
    // Cleanup code
}

StatusType oceans_t::add_fleet(int fleetId)
{
    if (fleetId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (fleets.find(fleetId) != nullptr) {
        return StatusType::FAILURE;
    }
    fleets.insert(fleetId, std::unique_ptr<Fleet>(new Fleet(fleetId)));
    return StatusType::SUCCESS;
}

StatusType oceans_t::add_pirate(int pirateId, int fleetId)
{
    if (pirateId <= 0 || fleetId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    if (pirates.find(pirateId) != nullptr || fleets.find(fleetId) == nullptr) {
        return StatusType::FAILURE;
    }
    Fleet* fleet = fleets.find(fleetId);
    int rank = fleet->getNumPirates() + 1;
    auto pirate = std::unique_ptr<Pirate>(new Pirate(pirateId, fleetId, rank));
    pirates.insert(pirateId, std::move(pirate));
    fleet->add_pirate(std::unique_ptr<Pirate>(new Pirate(pirateId, fleetId, rank)));
    return StatusType::SUCCESS;
}

StatusType oceans_t::pay_pirate(int pirateId, int salary)
{
    if (pirateId <= 0 || salary <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Pirate* pirate = pirates.find(pirateId);
    if (pirate == nullptr) {
        return StatusType::FAILURE;
    }
    pirate->add_money(salary);
    return StatusType::SUCCESS;
}

output_t<int> oceans_t::num_ships_for_fleet(int fleetId)
{
    if (fleetId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    Fleet* fleet = fleets.find(fleetId);
    if (fleet == nullptr) {
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>(fleet->getNumPirates());
}

output_t<int> oceans_t::get_pirate_money(int pirateId)
{
    if (pirateId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    Pirate* pirate = pirates.find(pirateId);
    if (pirate == nullptr) {
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>(pirate->get_money());
}

StatusType oceans_t::unite_fleets(int fleetId1, int fleetId2)
{
    if (fleetId1 <= 0 || fleetId2 <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Fleet* fleet1 = fleets.find(fleetId1);
    Fleet* fleet2 = fleets.find(fleetId2);
    if (fleet1 == nullptr || fleet2 == nullptr) {
        return StatusType::FAILURE;
    }
    Fleet* larger = (fleet1->getNumPirates() >= fleet2->getNumPirates()) ? fleet1 : fleet2;
    Fleet* smaller = (larger == fleet1) ? fleet2 : fleet1;
    larger->merge_with(smaller);
    fleets.remove(smaller->getId());
    return StatusType::SUCCESS;
}

StatusType oceans_t::pirate_argument(int pirateId1, int pirateId2)
{
    if (pirateId1 <= 0 || pirateId2 <= 0 || pirateId1 == pirateId2) {
        return StatusType::INVALID_INPUT;
    }
    Pirate* pirate1 = pirates.find(pirateId1);
    Pirate* pirate2 = pirates.find(pirateId2);
    if (pirate1 == nullptr || pirate2 == nullptr || pirate1->get_fleet_id() != pirate2->get_fleet_id()) {
        return StatusType::FAILURE;
    }
    if (pirate1->get_rank() < pirate2->get_rank()) {
        pirate1->receive_payment(pirate2->get_rank() - pirate1->get_rank());
        pirate2->pay(pirate2->get_rank() - pirate1->get_rank());
    } else {
        pirate2->receive_payment(pirate1->get_rank() - pirate2->get_rank());
        pirate1->pay(pirate1->get_rank() - pirate2->get_rank());
    }
    return StatusType::SUCCESS;
}
