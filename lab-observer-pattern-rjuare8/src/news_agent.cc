#include "news_agent.hpp"

// no need to modify this function
NewsAgent::NewsAgent(): location_(nullptr) {}

// no need to modify this function
void NewsAgent::ChangeLocation(Location* loc) {
  if (location_) {
    location_->RemoveAgent(this);
  }

  location_ = loc;

  if (location_) {
    location_->AddAgent(this);
  }
}

void NewsAgent::AddNewsChannelClient(NewsChannel* client) {
  channels_.push_back(client);
  // TODO : implement
}

void NewsAgent::RemoveNewsChannelClient(NewsChannel* client) {
  auto vect = channels_;
  channels_.clear();
  for (auto const& channel : vect) {
    if (channel != client) channels_.push_back(channel);
  }
  // TODO : implement
}

void NewsAgent::NotifyNews(std::string date,
                           std::string subject,
                           std::string action) {
  News news{location_->GetName(), date, subject, action};
  for (const auto& channel : channels_) channel->NotifyNews(news);

  // TODO : implement
}