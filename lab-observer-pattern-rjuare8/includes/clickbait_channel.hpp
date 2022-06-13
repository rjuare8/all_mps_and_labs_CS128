#ifndef CLICKBAIT_CHANNEL_HPP
#define CLICKBAIT_CHANNEL_HPP

#include "news_channel.hpp"

class ClickbaitChannel : public NewsChannel {
public:
  ClickbaitChannel() = default;
  ClickbaitChannel(std::ostream& out);

  void NotifyNews(const News& news) override;
};

#endif  // CLICKBAIT_CHANNEL_HPP