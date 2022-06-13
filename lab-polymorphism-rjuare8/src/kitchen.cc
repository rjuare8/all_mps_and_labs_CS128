#include "kitchen.hpp"

Kitchen::Kitchen(): Room("kitchen") {}

bool Kitchen::CanAddPerson() const { return true; }
