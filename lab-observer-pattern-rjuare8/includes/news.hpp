#ifndef NEWS_STRUCT_HPP
#define NEWS_STRUCT_HPP

#include <string>

struct News {
  std::string location;
  std::string date;
  std::string subject;
  std::string action;
};

#endif  // NEWS_STRUCT_HPP