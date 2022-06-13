#include "functions.hpp"

#include <cctype>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
// Your function definitions should go in this source file.
std::string Translate(std::string previous_word) {
  std::string reference = previous_word;
  std::string to_return;

  if (VerifyWord(reference)) {
    return previous_word +
           " contains a character not a part of the Hawaiian language.";
  }
  int length_previous_word = previous_word.length();

  for (int i = 0; i < length_previous_word; i++) {
    auto next_char = tolower(previous_word[i + 1]);
    if (tolower(previous_word[i]) == 'o') {
      std::string string_case_o =
          CaseCharacterO(previous_word, i, length_previous_word);
      to_return = PushinP(to_return, string_case_o);
      if (next_char == 'i' || next_char == 'u') {
        i++;
      } else if (next_char == ' ' || next_char == '\'') {
        to_return.pop_back();
      }
    } else if (tolower(previous_word[i]) == 'a') {
      std::string string_case_a =
          CaseCharacterA(previous_word, i, length_previous_word);
      for (const auto& ch : string_case_a) {
        to_return.push_back(ch);
      }
      if (next_char == 'i' || next_char == 'e' || next_char == 'o' ||
          next_char == 'u') {
        i++;
      } else if (next_char == ' ' || next_char == '\'') {
        to_return.pop_back();
      }
    } else if (tolower(previous_word[i]) == 'i') {
      std::string string_case_i =
          CaseCharacterI(previous_word, i, length_previous_word);
      for (const auto& ch : string_case_i) {
        to_return.push_back(ch);
      }
      if (next_char == 'u') {
        i++;
      } else if (next_char == ' ' || next_char == '\'') {
        to_return.pop_back();
      }
    } else if (tolower(previous_word[i]) == 'e') {
      std::string string_case_e =
          CaseCharacterE(previous_word, i, length_previous_word);
      for (const auto& ch : string_case_e) {
        to_return.push_back(ch);
      }
      if (next_char == 'i' || tolower(next_char) == 'u') {
        i++;
      } else if (next_char == ' ' || next_char == '\'') {
        to_return.pop_back();
      }
    } else if (previous_word[i] == 'u') {
      std::string string_case_u =
          CaseCharacterU(previous_word, i, length_previous_word);
      for (const auto& ch : string_case_u) {
        to_return.push_back(ch);
      }
      if (next_char == 'i') {
        i++;
      } else if (next_char == ' ' || next_char == '\'') {
        to_return.pop_back();
      }
    } else if (i > 0 && previous_word[i] == 'w' &&
               (previous_word[i - 1] == 'i' || previous_word[i - 1] == 'e')) {
      to_return.push_back('v');
    } else {
      to_return.push_back(tolower(previous_word[i]));
    }
  }
  previous_word = to_return;

  return to_return;
}

bool VerifyWord(const std::string WORD) {
  for (const auto& ch : WORD) {
    if (tolower(ch) == 'a' || tolower(ch) == 'e' || tolower(ch) == 'i' ||
        tolower(ch) == 'o' || tolower(ch) == 'u' || tolower(ch) == 'p' ||
        tolower(ch) == 'k' || tolower(ch) == 'h' || tolower(ch) == 'l' ||
        tolower(ch) == 'm' || tolower(ch) == 'n' || tolower(ch) == 'w' ||
        tolower(ch) == '\'' || tolower(ch) == ' ') {
    } else {
      return true;
    }
  }
  return false;
}

std::string CaseCharacterA(std::string to_return, int index, int length) {
  std::string case_a_string;
  auto char_after_a = tolower(to_return[index + 1]);
  if (index + 1 > length) {
    case_a_string = "ah-";
  } else if (char_after_a == 'i' || char_after_a == 'e') {
    case_a_string = "eye-";
  } else if (char_after_a == 'o' || char_after_a == 'u') {
    case_a_string = "ow-";
  } else {
    case_a_string = "ah-";
  }
  return case_a_string;
}

std::string CaseCharacterE(std::string to_return, int index, int length) {
  std::string case_e_string;
  auto char_after_e = tolower(to_return[index + 1]);
  if (index + 1 > length) {
    case_e_string = "eh-";
  } else if (char_after_e == 'i') {
    case_e_string = "ay-";
  } else if (char_after_e == 'u') {
    case_e_string = "eh-oo-";
  } else {
    case_e_string = "eh-";
  }
  return case_e_string;
}

std::string CaseCharacterI(std::string to_return, int index, int length) {
  std::string case_i_string;
  auto char_after_i = tolower(to_return[index + 1]);
  if (index + 1 > length) {
    case_i_string = "ee-";
  } else if (char_after_i == 'u') {
    case_i_string = "ew-";
  } else {
    case_i_string = "ee-";
  }
  return case_i_string;
}

std::string CaseCharacterO(std::string to_return, int index, int length) {
  std::string case_o_string;
  auto char_after_o = tolower(to_return[index + 1]);
  if (index + 1 > length) {
    case_o_string = "oh-";
  } else if (char_after_o == 'i') {
    case_o_string = "oy-";
  } else if (char_after_o == 'u') {
    case_o_string = "ow-";
  } else {
    case_o_string = "oh-";
  }
  return case_o_string;
}

std::string CaseCharacterU(std::string to_return, int index, int length) {
  std::string case_u_string;
  auto char_after_u = tolower(to_return[index + 1]);
  if (index + 1 > length) {
    case_u_string = "oo-";
  } else if (char_after_u == 'i') {
    case_u_string = "ooey-";
  } else {
    case_u_string = "oo-";
  }
  return case_u_string;
}

std::string PushinP(std::string to_return, std::string string_case) {
  for (const auto& ch : string_case) {
    to_return.push_back(ch);
  }
  return to_return;
}
