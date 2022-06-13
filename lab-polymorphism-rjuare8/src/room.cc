#include "room.hpp"

/* As you begin to develop Room, uncomment below */

Room::Room() {}

Room::Room(std::string room_name): name_(room_name) {}

std::string Room::GetName() const { return name_; }

const std::vector<std::string>& Room::GetPeople() const { return people_; }

void Room::AddPerson(std::string name) {
  if (CanAddPerson()) {
    people_.push_back(name);
  }
}

void Room::RemovePerson(std::string name) {
  for (size_t i = 0; i < people_.size(); ++i) {
    if (people_.at(i) == name) {
      people_.erase(people_.begin() + i);
      return;
    }
  }
}