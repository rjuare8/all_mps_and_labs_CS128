#include "informative_channel.hpp"

InformativeChannel::InformativeChannel(std::ostream& out): NewsChannel(out) {}

void InformativeChannel::NotifyNews(const News& news) {
  out_ << news.subject << " " << news.action << " on " << news.date << " in "
       << news.location << std::endl;
}