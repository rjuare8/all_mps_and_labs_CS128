#include "WordSearchSolver.hpp"

#include <cassert>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "CharPositions.hpp"
#include "WordLocation.hpp"

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordSearchSolver::WordSearchSolver(
    const std::vector<std::vector<char>>& puzzle):
    puzzle_(puzzle),
    puzzle_height_(puzzle.size()),
    puzzle_width_(puzzle.at(0).size()) {}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  WordLocation p;
  p.word = "not found";
  if (this->FindWord(word, CheckDirection::kHorizontal).word == word) {
    p = FindWord(word, CheckDirection::kHorizontal);
  } else if (this->FindWord(word, CheckDirection::kVertical).word == word) {
    p = FindWord(word, CheckDirection::kVertical);
  } else if (this->FindWord(word, CheckDirection::kRightDiag).word == word) {
    p = FindWord(word, CheckDirection::kRightDiag);
  } else if (this->FindWord(word, CheckDirection::kLeftDiag).word == word) {
    p = FindWord(word, CheckDirection::kLeftDiag);
  }

  return p;
}

WordLocation WordSearchSolver::FindWord(const std::string& word,
                                        CheckDirection direction) {
  WordLocation toreturn;
  if (direction == CheckDirection::kHorizontal) {
    toreturn = FindWordkHorizontal(word);
  } else if (direction == CheckDirection::kVertical) {
    toreturn = FindWordkVertical(word);
  } else if (direction == CheckDirection::kLeftDiag) {
    toreturn = FindWordkLeftDiag(word);
  } else if (direction == CheckDirection::kRightDiag) {
    toreturn = FindWordkRightDiag(word);
  }

  return toreturn;
}

WordLocation WordSearchSolver::FindWordkHorizontal(const std::string& word) {
  for (int row = 0; row < (int)puzzle_height_; row++) {
    int index = 0;
    WordLocation toreturn;
    toreturn.word = word;
    for (int col = 0; col < (int)puzzle_width_; col++) {
      toreturn.word = word;

      if (puzzle_.at(row).at(col) == word[index]) {
        toreturn.char_positions.push_back(CharToAdd(word[index], row, col));
        index++;

        if (index == (int)word.size()) {
          return toreturn;
        }
      } else {
        toreturn.char_positions = {};
        index = 0;
        if (puzzle_.at(row).at(col) == word[index]) {
          toreturn.char_positions.push_back(CharToAdd(word[index], row, col));
          index++;
        }
        if (index == (int)word.size()) {
          return toreturn;
        }
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWordkVertical(const std::string& word) {
  for (int col = 0; col < (int)puzzle_width_; col++) {
    int index = 0;
    WordLocation toreturn;
    toreturn.word = word;
    for (int row = 0; row < (int)puzzle_height_; row++) {
      if (puzzle_.at(row).at(col) == word[index]) {
        toreturn.char_positions.push_back(CharToAdd(word[index], row, col));
        index++;

        if (index == (int)word.size()) {
          return toreturn;
        }
      } else {
        toreturn.char_positions = {};
        index = 0;
        if (puzzle_.at(row).at(col) == word[index]) {
          toreturn.char_positions.push_back(CharToAdd(word[index], row, col));
          index++;
        }
        if (index == (int)word.size()) {
          return toreturn;
        }
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWordkRightDiag(const std::string& word) {
  for (int col = 0; col < (int)puzzle_width_; col++) {
    WordLocation toreturn;
    toreturn.word = word;
    int count = 0;
    for (int row = 0; row < (int)puzzle_height_; row++) {
      int index = count;
      if (LocationInBounds(row + (int)word.size() - 1, col + word.size() - 1)) {
        for (int diag = 0; diag < (int)word.size(); diag++) {
          if (puzzle_.at(row + diag).at(col + diag) == word[index]) {
            toreturn.char_positions.push_back(
                CharToAdd(word[index], row + diag, col + diag));
            index++;

            if (index == (int)word.size()) {
              return toreturn;
            }
          } else {
            toreturn.char_positions = {};
            index = 0;
            if (puzzle_.at(row + diag).at(col + diag) == word[index]) {
              toreturn.char_positions.push_back(
                  CharToAdd(word[index], row + diag, col + diag));
              index++;
              count++;

              if (index == (int)word.size()) {
                return toreturn;
              }
            }
          }
        }
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWordkLeftDiag(const std::string& word) {
  for (int col = 0; col < (int)puzzle_width_; col++) {
    WordLocation toreturn;
    toreturn.word = word;
    int count = 0;
    for (int row = 0; row < (int)puzzle_height_; row++) {
      int index = count;

      if (LocationInBounds(row + (int)word.size() - 1,
                           col - (int)word.size() + 1)) {
        for (int diag = 0; diag < (int)word.size(); diag++) {
          if (puzzle_.at(row + diag).at(col - diag) == word[index]) {
            toreturn.char_positions.push_back(
                CharToAdd(word[index], row + diag, col - diag));
            index++;

            if (index == (int)word.size()) {
              return toreturn;
            }
          } else {
            toreturn.char_positions = {};
            index = 0;
            if (puzzle_.at(row + diag).at(col + diag) == word[index]) {
              toreturn.char_positions.push_back(
                  CharToAdd(word[index], row + diag, col - diag));
              index++;
              count++;

              if (index == (int)word.size()) {
                return toreturn;
              }
            }
          }
        }
      }
    }
  }
  return WordLocation{};
}

CharPositions WordSearchSolver::CharToAdd(char character, int row, int col) {
  CharPositions letra{};
  letra.character = character;
  letra.row = row;
  letra.col = col;
  return letra;
}
