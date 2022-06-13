#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  // below was minimal to get tests to actually compile and given test case to
  // fail
  for (int i = 0; i < Board::kBoardWidth; i++) {
    for (int j = 0; j < Board::kBoardHeight; j++) {
      b.board[j][i] = DiskType::kEmpty;
    }
  }
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col >= Board::kBoardWidth || col < 0) {
    throw std::runtime_error("column is out of range");
  }
  for (int i = 0; i < Board::kBoardHeight; i++) {
    if (b.board[i][col] == DiskType::kEmpty) {
      b.board[i][col] = disk;
      return;
    }
  }
  throw std::runtime_error("rows is out of range");
}

bool CheckForWinner(Board& b, DiskType disk) {
  return SearchForWinner(b, disk, WinningDirection::kHorizontal) ||
         SearchForWinner(b, disk, WinningDirection::kVertical) ||
         SearchForWinner(b, disk, WinningDirection::kLeftDiag) ||
         SearchForWinner(b, disk, WinningDirection::kRightDiag);
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  // check if the disk type wins based on the winning direction
  bool result = false;
  if (to_check ==
      WinningDirection::kHorizontal) {  // checks on the horizontal direction
    result = SearchForWinnerHorizontal(b, disk);

  } else if (to_check ==
             WinningDirection::kVertical) {  // checks on the vertical direction
    result = SearchForWinnerVertical(b, disk);

  } else if (to_check == WinningDirection::kLeftDiag) {  // checks on the left
                                                         // diagnal direction
    result = SearchForWinnerLeftDiag(b, disk);

  } else if (to_check == WinningDirection::kRightDiag) {
    result = SearchForWinnerRightDiag(b, disk);
  }
  return result;
}

bool BoardLocationInBounds(int row, int col) {
  return !(row >= Board::kBoardHeight || col >= Board::kBoardWidth || row < 0 ||
           col < 0);
}

bool SearchForWinnerHorizontal(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardHeight; i++) {
    int count = 0;
    for (int j = 0; j < Board::kBoardWidth; j++) {
      if (b.board[i][j] == disk) {
        count++;
        if (count == 4) {
          return true;
        }
      } else {
        count = 0;
      }
    }
  }
  return false;
}

bool SearchForWinnerVertical(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardWidth; i++) {
    int count = 0;
    for (int j = 0; j < Board::kBoardHeight; j++) {
      if (b.board[j][i] == disk) {
        count++;
        if (count == 4) {
          return true;
        }
      } else {
        count = 0;
      }
    }
  }
  return false;
}
bool SearchForWinnerRightDiag(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardWidth; i++) {
    for (int j = 0; j < Board::kBoardHeight; j++) {
      int count = 0;
      if (BoardLocationInBounds(j + 3, i + 3)) {
        for (int k = 0; k < 4; k++) {
          if (b.board[j + k][i + k] == disk) {
            count++;
            if (count == 4) {
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}
bool SearchForWinnerLeftDiag(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardWidth; i++) {
    for (int j = 0; j < Board::kBoardHeight; j++) {
      // std::cout << "column : " << i << " row : " << j << std::endl;
      int count = 0;
      if (BoardLocationInBounds(j - 3, i + 3)) {
        for (int k = 0; k < 4; k++) {
          if (b.board[j - k][i + k] == disk) {
            count++;
            std::cout << count << std::endl;
            if (count == 4) {
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}
