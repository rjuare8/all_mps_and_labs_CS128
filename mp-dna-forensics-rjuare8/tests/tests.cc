#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include <catch/catch.hpp>
#include <string>

#include "functions.hpp"

// trying to make a helper method that finds how many times a str appear in
TEST_CASE("A test case", "[case-1]") {
  bool something = true;
  REQUIRE(something == true);
}
