#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "utilities.hpp"

std::vector<std::vector<std::string>> DNASequenceOrganizer(std::ifstream file);

std::string DNAAnalysis(std::vector<std::vector<std::string>> dna_database,
                        std::string tested_dna);

int STRCounter(std::string str, std::string dna_test);

std::string STRIdentifier(std::vector<int> str_from_string,
                          std::vector<std::vector<std::string>> dna_database);

#endif