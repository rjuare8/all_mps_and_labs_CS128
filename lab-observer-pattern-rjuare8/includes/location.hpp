#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>
#include <vector>

class NewsAgent;

class Location {
public:
  Location() = delete;
  Location(std::string name);
  void AddAgent(NewsAgent* agent);
  void RemoveAgent(NewsAgent* agent);
  void Event(std::string date, std::string subject, std::string action);

  std::string GetName() const;

private:
  std::vector<NewsAgent*> agents_;
  std::string name_;
};

#endif  // LOCATION_HPP