#include "cord-utilities.hpp"

std::shared_ptr<Cord> ConcatCords(std::shared_ptr<Cord> left_cord,
                                  std::shared_ptr<Cord> right_cord) {
  if (left_cord == nullptr) {
    if (!right_cord->IsValidCord()) {
      throw std::invalid_argument("not valid cord");
    }
    return right_cord;
  }

  if (right_cord == nullptr) {
    if (!left_cord->IsValidCord()) {
      throw std::invalid_argument("not valid cords");
    }
    return left_cord;
  }

  if (!left_cord->IsValidCord() || !right_cord->IsValidCord())
    throw std::invalid_argument("not valid cords");

  // if (left_cord == nullptr) return right_cord;
  // if (right_cord == nullptr) return left_cord;

  std::shared_ptr<Cord> concat = std::make_shared<Cord>(left_cord, right_cord);

  return concat;
}

void ReduceCords(cs128::ReferenceList<std::shared_ptr<Cord>> cords) {
  std::map<std::string, std::shared_ptr<Cord>> visited = {};

  for (const auto& cord : cords) {
    cord.get()->CheckCords(visited, cord);
    /*std::cout << "test" << std::endl;
    for (const auto& key : visited) {
      std::cout << key.first << std::endl;
    }*/
  }
  // TODO
}
