#include "solution.hpp"

unsigned int StrLen(const char* c_str) {
  int i = 0;
  while (c_str[i] != '\0') {
    i++;
  }
  return i;
}

void StrCpy(char*& to, const char* from) {
  if (from == nullptr) {
    return;
  }

  char* tmp = new char[StrLen(from) + 1];
  for (unsigned int i = 0; i < StrLen(from); i++) {
    tmp[i] = from[i];
  }
  tmp[StrLen(from)] = '\0';

  delete[] to;

  to = tmp;
}