#ifndef NEWS_AGENT_HPP
#define NEWS_AGENT_HPP

#include <string>
#include <vector>

#include "news.hpp"
#include "news_channel.hpp"

class Location;  // forward declaration

class NewsAgent {
public:
  NewsAgent();
  void AddNewsChannelClient(NewsChannel* client);
  void RemoveNewsChannelClient(NewsChannel* client);
  void ChangeLocation(Location* loc);
  void NotifyNews(std::string date, std::string subject, std::string action);

private:
  std::vector<NewsChannel*> channels_;
  Location* location_;
};

#include "location.hpp"

#endif  // NEWS_AGENT_HPP