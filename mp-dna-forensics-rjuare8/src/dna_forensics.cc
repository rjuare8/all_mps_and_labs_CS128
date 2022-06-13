#include <fstream>
#include <iostream>
#include <map>

#include "functions.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }
  std::vector<std::vector<std::string>> dna_database =
      DNASequenceOrganizer((std::ifstream)argv[1]);

  /*for (unsigned int i = 0; i < dna_database.size(); i++) {
    for (unsigned int j = 0; j < dna_database[i].size(); j++) {
      std::cout << dna_database[i][j] << " ";
    }
    std::cout << std::endl;
  }*/

  std::string result_test = DNAAnalysis(dna_database, argv[2]);

  std::cout << result_test << std::endl;

  return 0;
}