#include "living-room.hpp"

LivingRoom::LivingRoom(): Room("living room") {}

bool LivingRoom::CanAddPerson() const { return true; }

void LivingRoom::RemovePerson(std::string name) {
  size_t size_bef = people_.size();
  Room::RemovePerson(name);
  if (size_bef != people_.size()) {
    people_.erase(people_.begin());
  }
}