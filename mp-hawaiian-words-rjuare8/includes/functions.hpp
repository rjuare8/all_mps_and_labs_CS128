#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <string>
#include <vector>

// Your function declarations should go in this header file.
std::string Translate(std::string previous_word);

bool VerifyWord(std::string WORD);

std::string PushinP(std::string to_return, std::string string_case);

std::string CaseCharacterA(std::string to_return, int index, int length);
std::string CaseCharacterE(std::string to_return, int index, int length);
std::string CaseCharacterI(std::string to_return, int index, int length);
std::string CaseCharacterO(std::string to_return, int index, int length);
std::string CaseCharacterU(std::string to_return, int index, int length);

std::vector<int> get_ints_from_file(std::string file_name);

#endif