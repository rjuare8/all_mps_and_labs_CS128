#include "bathroom.hpp"

Bathroom::Bathroom(): Room("bathroom") {}

bool Bathroom::CanAddPerson() const {
  bool to_return = true;
  if (people_.size() == 1) {
    to_return = false;
  }
  return to_return;
}
