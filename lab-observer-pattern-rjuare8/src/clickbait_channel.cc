#include "clickbait_channel.hpp"

ClickbaitChannel::ClickbaitChannel(std::ostream& out): NewsChannel(out) {}

void ClickbaitChannel::NotifyNews(const News& news) {
  out_ << "You won't believe what " << news.subject << " did!!" << std::endl;
}