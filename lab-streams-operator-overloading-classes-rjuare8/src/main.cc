#include "iostream"
#include "student.hpp"

int main() {
  Student st("Ike South", "0000000", "ike");
  Course phys;
  phys.credits = 2;
  phys.name = "PHYS211";
  Course cs;
  cs.credits = 3;
  cs.name = "CS218";
  Course rhet;
  rhet.credits = 5;
  rhet.name = "RHET101";
  st.AddCourse(phys);
  st.AddCourse(cs);
  st.AddCourse(rhet);
  std::cout << st;
  return 0;
}
