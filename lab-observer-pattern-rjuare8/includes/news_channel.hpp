#ifndef NEWS_CHANNEL_HPP
#define NEWS_CHANNEL_HPP

#include <iostream>
#include <string>

#include "news.hpp"

class NewsChannel {
public:
  NewsChannel();
  NewsChannel(std::ostream& out);

  virtual void NotifyNews(const News& news) = 0;

protected:
  std::ostream& out_;
};

#endif  // NEWS_CHANNEL_HPP