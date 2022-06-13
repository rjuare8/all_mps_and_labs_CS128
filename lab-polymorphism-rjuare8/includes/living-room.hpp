#ifndef LIVING_ROOM_HPP
#define LIVING_ROOM_HPP

#include "room.hpp"

class LivingRoom : public Room {
public:
  LivingRoom();

  void RemovePerson(std::string name);

protected:
  bool CanAddPerson() const;
};

#endif  // LIVING_ROOM_HPP
