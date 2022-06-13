#include <cassert>
#include <iostream>
#include <memory>

#include "cord-utilities.hpp"
#include "cord.hpp"

int main() {
  std::shared_ptr<Cord> ptr1 = std::make_shared<Cord>("8 is awe");
  std::shared_ptr<Cord> ptr2 = std::make_shared<Cord>("some");

  std::shared_ptr<Cord> ptr3 = std::make_shared<Cord>(ptr1, ptr2);
  std::shared_ptr<Cord> ptr4 = std::make_shared<Cord>("CS12");

  Cord cord1(ptr4, ptr3);

  std::cout << cord1.ToString() << std::endl;
  std::cout << cord1.At(3) << std::endl;

  std::shared_ptr<Cord> ptr10 = std::make_shared<Cord>("he");
  std::shared_ptr<Cord> ptr11 = std::make_shared<Cord>("llo");
  std::shared_ptr<Cord> ptr12 = std::make_shared<Cord>("wor");
  std::shared_ptr<Cord> ptr13 = std::make_shared<Cord>("ld");

  std::shared_ptr<Cord> ptr14 = std::make_shared<Cord>(ptr10, ptr11);
  std::shared_ptr<Cord> ptr15 = std::make_shared<Cord>(ptr12, ptr13);

  Cord cord2(ptr14, ptr15);

  std::cout << cord2.ToString() << std::endl;
  std::cout << cord2.Length() << std::endl;
  std::cout << "sub test: " << cord2.SubString(2, 8)->ToString() << "<--- "
            << std::endl;
  std::cout << "sub test: " << cord2.SubString(2, 7)->ToString() << "<--- "
            << std::endl;
  std::cout << "sub test: " << cord2.SubString(3, 6)->ToString() << "<--- "
            << std::endl;
  std::cout << "sub test: " << cord2.SubString(3, 5)->ToString() << "<--- "
            << std::endl;
  std::cout << "sub test: " << cord2.SubString(3, 9)->ToString() << "<--- "
            << std::endl;

  std::shared_ptr<Cord> ptr16 = std::make_shared<Cord>("pre");
  std::shared_ptr<Cord> ptr17 = std::make_shared<Cord>("po");
  std::shared_ptr<Cord> ptr18 = std::make_shared<Cord>("sse");
  std::shared_ptr<Cord> ptr19 = std::make_shared<Cord>("ssion");

  std::shared_ptr<Cord> ptr20 = std::make_shared<Cord>(ptr18, ptr19);
  std::shared_ptr<Cord> ptr21 = std::make_shared<Cord>(ptr17, ptr20);

  std::shared_ptr<Cord> cord3 = std::make_shared<Cord>(ptr16, ptr21);

  std::cout << cord3->ToString() << std::endl;
  std::cout << cord3->Length() << std::endl;
  std::cout << cord3->SubString(2, 13)->ToString() << "<----" << std::endl;

  std::shared_ptr<Cord> reduce1 = std::make_shared<Cord>("nonpo");
  std::shared_ptr<Cord> reduce2 = std::make_shared<Cord>("ssession");

  std::shared_ptr<Cord> reduce3 = std::make_shared<Cord>(reduce1, reduce2);

  std::shared_ptr<Cord> reduce4 = std::make_shared<Cord>("possession");

  std::shared_ptr<Cord> reduce5 = std::make_shared<Cord>("pro");
  std::shared_ptr<Cord> reduce6 = std::make_shared<Cord>("fe");
  std::shared_ptr<Cord> reduce7 = std::make_shared<Cord>("ssion");

  std::shared_ptr<Cord> reduce8 = std::make_shared<Cord>(reduce6, reduce7);
  std::shared_ptr<Cord> reduce9 = std::make_shared<Cord>(reduce5, reduce8);

  std::cout << cord3->ToString() << std::endl;
  std::cout << reduce9->ToString() << std::endl;
  std::cout << reduce4->ToString() << std::endl;
  std::cout << reduce3->ToString() << std::endl;

  cs128::ReferenceList<std::shared_ptr<Cord>> cords = {
      cord3, reduce9, reduce4, reduce3};

  for (const auto& cord : cords) {
    std::cout << cord.get() << std::endl;
    if (cord.get()->GetLeft() != nullptr && cord.get()->GetRight() != nullptr) {
      std::cout << "Left cord: " << cord.get()->GetLeft()
                << " Right cord: " << cord.get()->GetRight() << std::endl;
    }
  }

  ReduceCords(cords);

  std::cout << "//////////Test Reduce Cords/////////" << std::endl;

  for (const auto& cord : cords) {
    std::cout << cord.get() << std::endl;
    if (cord.get()->GetLeft() != nullptr && cord.get()->GetRight() != nullptr) {
      std::cout << "Left cord: " << cord.get()->GetLeft()
                << " Right cord: " << cord.get()->GetRight() << std::endl;
    }
  }

  return 0;
}
