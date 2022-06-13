
/* Framework setup */
#include "catch.hpp"

/* Includes */
#include <iostream>
#include <sstream>
#include <string>

#include "course.hpp"
#include "student.hpp"

/* Helpers/Constants */

/* Test Cases */

TEST_CASE("Overloaded Operator", "[operator]") {
  SECTION("Minimal") {
    std::ostringstream ss;
    std::string ans =
        "Name: Ike South\nUIN: 000000000\nNet Id: ike\nMajor: "
        "Undeclared\nCredits: 0\nCourses: \nGraduated: False";
    Student st("Ike South", "000000000", "ike");
    ss << st;
    REQUIRE(ss.str() == ans);
  }
}