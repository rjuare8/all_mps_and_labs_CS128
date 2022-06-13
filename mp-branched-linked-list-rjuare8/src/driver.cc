#include <iostream>

#include "branched-linked-list.hpp"

int main() {
  /* EXAMPLE INTERACTIONS WITH BLL */
  BLL* first = new BLL();
  first->PushBack('h');
  first->PushBack('i');

  std::cout << first->ToString() << std::endl;  // hi
  std::cout << first->Size() << std::endl;      //
  /////////////////////////////////////

  BLL* second = new BLL();
  second->PushBack('i');
  second->PushBack('!');
  second->PushBack('@');

  std::cout << second->ToString() << std::endl;  // i!@
  std::cout << second->Size() << std::endl;      // 3
                                                 //
  //// /////////////////////////////////////
  //
  first->Join(1, second);
  //
  std::cout << first->ToString() << std::endl;  // hii!@
  std::cout << first->Size() << std::endl;      // 5
  //                                               //
  std::cout << second->ToString() << std::endl;  // i!@
  std::cout << second->Size() << std::endl;      // 3

  // first->~BLL();

  //
  //// /////////////////////////////////////
  //
  BLL* first_clone(first);
  // BLL* first_clone = new BLL();
  // std::cout << "clone test: " << first_clone->ToString() << std::endl;
  /// / hii!@

  //*first_clone = *first;

  std::cout << "clone test: " << first_clone->ToString() << std::endl;  //
  //
  std::cout << first_clone->Size() << std::endl;  // 5 std::cout <<
  std::cout << first_clone->GetAt(3) << std::endl;
  std::cout << first_clone->GetAt(4) << std::endl;
  first_clone->SetAt(0, 't');
  first_clone->SetAt(1, 'e');
  first_clone->SetAt(2, 's');
  first_clone->SetAt(3, 't');
  first_clone->SetAt(4, '!');

  delete first_clone;
  delete first;

  std::cout << "SetAt test: " << first_clone->ToString() << std::endl;
  //
  BLL* third = new BLL();
  third->PushBack('1');
  third->PushBack('2');
  third->PushBack('3');

  BLL* fourth = new BLL();
  fourth->PushBack('4');
  fourth->PushBack('5');
  fourth->PushBack('7');

  BLL* fifth = new BLL();
  fifth->PushBack('6');

  third->Join(2, fourth);
  fourth->Join(1, fifth);

  delete third;

  // BLL* clone2 = new BLL();
  //*clone2 = *third;
  // clone2->~BLL();
  //
  // std::cout << "Clone test: " << third->ToString() << std::endl;
  //
  // std::cout << "El correme que me atrapas test " << std::endl;
  //
  // BLL* test1 = new BLL();
  // test1->PushBack('0');
  // test1->PushBack('1');
  // test1->PushBack('2');
  //
  // BLL* test2 = new BLL();
  // test2->PushBack('3');
  // test2->PushBack('4');
  // test2->PushBack('9');
  //
  // BLL* test3 = new BLL();
  // test3->PushBack('5');
  // test3->PushBack('6');
  // test3->PushBack('7');
  //
  // BLL* test4 = new BLL();
  // test4->PushBack('8');
  //
  // test1->Join(2, test2);
  // test2->Join(1, test3);
  // test3->Join(2, test4);
  //// test4->Join(0, test2);
  //
  // test1->~BLL();
  //
  // std::cout << test1->ToString() << std::endl;
  //
  // test4->~BLL();
  //
  // BLL* test9 = new BLL();
  // test9->PushBack('8');
  // test9->PushBack('8');
  //
  // BLL* test5 = new BLL();
  // test5->PushBack('8');
  // test5->PushBack('9');
  // test5->PushBack('9');
  // test5->PushBack('9');
  //
  // BLL* test6 = new BLL();
  // test6->PushBack('8');
  //
  //// test9->Join(0, test5);
  //// test5->Join(0, test6);
  //
  // BLL* test7(test9);
  //
  // std::cout << test7->ToString() << std::endl;

  return 0;
}
