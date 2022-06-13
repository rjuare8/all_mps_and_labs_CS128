#ifndef INFORMATIVE_CHANNEL_HPP
#define INFORMATIVE_CHANNEL_HPP

#include "news_channel.hpp"

class InformativeChannel : public NewsChannel {
public:
  InformativeChannel() = default;
  InformativeChannel(std::ostream& out);

  void NotifyNews(const News& news) override;
};

#endif  // INFORMATIVE_CHANNEL_HPP
