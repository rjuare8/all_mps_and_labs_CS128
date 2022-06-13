#include <iostream>
#include <string>

#include "functions.hpp"

int main(int argc, char* argv[]) {
  int v = argc;
  v++;
  std::cout << Translate(argv[1]) << std::endl;
}