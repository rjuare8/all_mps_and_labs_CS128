#include <iostream>

#include "illini_book.hpp"

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    std::cout << "illegal number of arguments" << std::endl;
    return 0;
  }

  std::cout << argv[1] << argv[2] << std::endl;

  IlliniBook book(argv[1], argv[2]);

  std::cout << book.AreRelated(1, 2) << book.AreRelated(3, 2)
            << book.AreRelated(1, 9) << std::endl;

  std::cout << book.AreRelated(1, 2, "128") << book.AreRelated(1, 2, "124")
            << book.AreRelated(1, 6, "128") << book.AreRelated(1, 6, "124")
            << std::endl;

  std::cout << book.GetRelated(1, 2) << book.GetRelated(3, 2)
            << book.GetRelated(1, 9) << std::endl;

  std::cout << book.GetRelated(1, 2, "128") << book.GetRelated(1, 2, "124")
            << book.GetRelated(1, 6, "128") << book.GetRelated(1, 6, "124")
            << std::endl;

  std::vector<int> vec1 = book.GetSteps(1, 1);
  std::vector<int> vec2 = book.GetSteps(1, 2);
  std::vector<int> vec3 = book.GetSteps(1, 3);
  std::vector<int> vec4 = book.GetSteps(9, 1);

  for (auto const& node : vec1) std::cout << node << std::endl;
  for (auto const& node : vec2) std::cout << node << std::endl;
  for (auto const& node : vec3) std::cout << node << std::endl;
  for (auto const& node : vec4) std::cout << node << std::endl;

  std::cout << book.CountGroups() << std::endl;

  std::cout << book.CountGroups("124") << std::endl;
  std::cout << book.CountGroups("128") << std::endl;
  std::cout << book.CountGroups("173") << std::endl;

  std::cout << book.CountGroups(std::vector<std::string>{"128", "173"})
            << std::endl;
  std::cout << book.CountGroups(std::vector<std::string>{"128", "124", "173"})
            << std::endl;

  return 0;
}
