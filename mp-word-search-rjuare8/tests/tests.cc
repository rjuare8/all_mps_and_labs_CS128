// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Location in bounds", "[Location]") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                        {'h', 'e', 'l', 'l', 'o'},
                                        {'c', 'a', 'l', 'o', 'm'},
                                        {'a', 'e', 't', 'a', 'u'},
                                        {'t', 'e', 't', 'o', 'u'}};

  WordSearchSolver wss(puzzle);
}

TEST_CASE("WordSearch Horizotal direction", "[kHorizontal]") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                        {'h', 'e', 'l', 'l', 'o'},
                                        {'c', 'a', 'l', 'o', 'm'},
                                        {'h', 'e', 'l', 'l', 'o'},
                                        {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver wss(puzzle);
  WordLocation result = wss.FindWord("hello");

  std::cout << result << std::endl;

  REQUIRE(result.word == "hello");
  REQUIRE_FALSE(result.word == "aetau");
  REQUIRE(result.char_positions.at(0).character == 'h');
  REQUIRE(result.char_positions.at(0).col == 0);
  REQUIRE(result.char_positions.at(0).row == 1);
  REQUIRE(result.char_positions.at(1).character == 'e');
  REQUIRE(result.char_positions.at(1).col == 1);
  REQUIRE(result.char_positions.at(1).row == 1);
  REQUIRE(result.char_positions.at(2).character == 'l');
  REQUIRE(result.char_positions.at(2).col == 2);
  REQUIRE(result.char_positions.at(2).row == 1);
  REQUIRE(result.char_positions.at(3).character == 'l');
  REQUIRE(result.char_positions.at(3).col == 3);
  REQUIRE(result.char_positions.at(3).row == 1);
  REQUIRE(result.char_positions.at(4).character == 'o');
  REQUIRE(result.char_positions.at(4).col == 4);
  REQUIRE(result.char_positions.at(4).row == 1);
}

TEST_CASE("WordSearch Vertical direction", "[kVertical]") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'c', 'o', 'u'},
                                        {'c', 'h', 'a', 't', 'o'},
                                        {'c', 'c', 'l', 'o', 'd'},
                                        {'a', 'e', 't', 'a', 'a'},
                                        {'t', 'e', 't', 'o', 't'}};
  WordSearchSolver wss(puzzle);
  WordLocation result = wss.FindWord("cat");

  std::cout << result << std::endl;

  REQUIRE(result.word == "cat");
  REQUIRE_FALSE(result.word == "ltt");
  REQUIRE(result.char_positions.at(0).character == 'c');
  REQUIRE(result.char_positions.at(0).col == 0);
  REQUIRE(result.char_positions.at(0).row == 2);
  REQUIRE(result.char_positions.at(1).character == 'a');
  REQUIRE(result.char_positions.at(1).col == 0);
  REQUIRE(result.char_positions.at(1).row == 3);
  REQUIRE(result.char_positions.at(2).character == 't');
  REQUIRE(result.char_positions.at(2).col == 0);
  REQUIRE(result.char_positions.at(2).row == 4);
}

TEST_CASE("WordSearch Right Diagnol", "[kRightDiag]") {
  std::vector<std::vector<char>> puzzle{{'d', 'l', 'a', 'o', 'u'},
                                        {'h', 'e', 'l', 'l', 'o'},
                                        {'c', 'a', 'l', 'o', 'm'},
                                        {'a', 'e', 't', 'a', 'u'},
                                        {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver wss(puzzle);
  WordLocation result = wss.FindWord("lou");

  std::cout << result << std::endl;
  REQUIRE(result.word == "lou");
  REQUIRE_FALSE(result.word == "mat");
  REQUIRE(result.char_positions.at(0).character == 'l');
  REQUIRE(result.char_positions.at(0).col == 2);
  REQUIRE(result.char_positions.at(0).row == 1);
  REQUIRE(result.char_positions.at(1).character == 'o');
  REQUIRE(result.char_positions.at(1).col == 3);
  REQUIRE(result.char_positions.at(1).row == 2);
  REQUIRE(result.char_positions.at(2).character == 'u');
  REQUIRE(result.char_positions.at(2).col == 4);
  REQUIRE(result.char_positions.at(2).row == 3);
}

TEST_CASE("WordSearch Left Diagnol", "[kLeftDiag]") {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                        {'h', 'e', 'l', 'l', 'o'},
                                        {'c', 'a', 'l', 'o', 'm'},
                                        {'a', 'e', 't', 'a', 'u'},
                                        {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver wss(puzzle);
  WordLocation result = wss.FindWord("oote");

  std::cout << result << std::endl;
  REQUIRE(result.word == "oote");
  REQUIRE_FALSE(result.word == "ullet");
  REQUIRE(result.char_positions.at(0).character == 'o');
  REQUIRE(result.char_positions.at(0).col == 4);
  REQUIRE(result.char_positions.at(0).row == 1);
  REQUIRE(result.char_positions.at(1).character == 'o');
  REQUIRE(result.char_positions.at(1).col == 3);
  REQUIRE(result.char_positions.at(1).row == 2);
  REQUIRE(result.char_positions.at(2).character == 't');
  REQUIRE(result.char_positions.at(2).col == 2);
  REQUIRE(result.char_positions.at(2).row == 3);
  REQUIRE(result.char_positions.at(3).character == 'e');
  REQUIRE(result.char_positions.at(3).col == 1);
  REQUIRE(result.char_positions.at(3).row == 4);
}

/////////////////////////////////////////////////////////////////////////////////////////////