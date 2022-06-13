#include "news_channel.hpp"

NewsChannel::NewsChannel(): out_(std::cout) {}

NewsChannel::NewsChannel(std::ostream& out): out_(out) {}
