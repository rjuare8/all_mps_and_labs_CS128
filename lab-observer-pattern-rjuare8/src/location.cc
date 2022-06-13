#include "news_agent.hpp"

// no need to modify this function
Location::Location(std::string name): name_(name) {}

// no need to modify this function
std::string Location::GetName() const { return name_; }

void Location::AddAgent(NewsAgent* agent) {
  agents_.push_back(agent);
  // TODO : implement
}

void Location::RemoveAgent(NewsAgent* agent) {
  auto vect = agents_;
  agents_.clear();
  for (auto const& agent1 : vect) {
    if (agent1 != agent) agents_.push_back(agent1);
  }
  // TODO : implement
}

void Location::Event(std::string date,
                     std::string subject,
                     std::string action) {
  for (auto const& agent : agents_) agent->NotifyNews(date, subject, action);
  // TODO : implement
}
