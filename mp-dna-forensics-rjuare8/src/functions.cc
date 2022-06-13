#include "functions.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "utilities.hpp"

// Function that return a 2D vector with the information of the dna extracted
// from the .dat file
std::vector<std::vector<std::string>> DNASequenceOrganizer(std::ifstream file) {
  std::vector<std::vector<std::string>> dna_database;
  for (std::string line; std::getline(file, line); line = "") {
    // std::cout << "line = \"" << line << '\"' << std::endl;
    std::vector<std::string> words_in_line = utilities::GetSubstrs(line, ',');
    dna_database.push_back(words_in_line);
  }
  return dna_database;
}

std::string DNAAnalysis(std::vector<std::vector<std::string>> dna_database,
                        std::string tested_dna) {
  std::string result;  // string that will return the name of the person that it
                       // is the test or 'No match'

  std::vector<int> strs_from_strings;
  for (unsigned int i = 1; i < dna_database[0].size(); i++) {
    // Make each of the STR to char array
    // std::cout << "test" << std::endl;
    // Compare the input string to each of the STR
    int str_counter = STRCounter(dna_database[0][i], tested_dna);
    // std::cout << str_counter << std::endl;
    strs_from_strings.push_back(str_counter);
  }

  return STRIdentifier(strs_from_strings, dna_database);
}

// trying to make a helper method that finds how many times a str appear in
// a row currently trying to figure how to reset the count so it does count the
// str that are not in order
int STRCounter(std::string str, std::string dna_test) {
  int count = 0;
  int largest_str_inrow = int(dna_test.length() / str.length());
  std::string possible_str = str;
  for (int i = 0; i < largest_str_inrow; i++) {
    std::size_t found = dna_test.find(possible_str);
    if (found != std::string::npos) {
      count = int(possible_str.length() / str.length());
    }
    possible_str += str;
  }
  // std::cout << count << " for str " << str << " in dna test " << dna_test
  //<< std::endl;
  return count;
}

std::string STRIdentifier(std::vector<int> str_from_string,
                          std::vector<std::vector<std::string>> dna_database) {
  std::string string_to_return;
  std::vector<int> test = str_from_string;
  std::map<std::string, std::vector<int>> map_dna;
  for (unsigned int i = 1; i < dna_database.size(); i++) {
    std::vector<int> str_int;
    // convert strings to numbers so they can be compared to the vector of
    // strings
    for (unsigned int j = 1; j < dna_database[i].size(); j++) {
      // std::cout << dna_database[i][j] << " ";
      str_int.push_back(std::stoi(dna_database[i][j]));
    }
    map_dna.insert(
        std::pair<std::string, std::vector<int>>(dna_database[i][0], str_int));
  }

  for (const auto& pair : map_dna) {
    // std::cout << pair.first << " ";
    if (pair.second == test) {
      return pair.first;
    }
  }
  return "No match";
}