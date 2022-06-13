#include <iostream>

#include "clickbait_channel.hpp"
#include "informative_channel.hpp"
#include "news_agent.hpp"
#include "news_channel.hpp"

int main() {
  Location champaign_loc("Champaign");
  Location cypress_loc("Cypress");

  ClickbaitChannel clickbait;
  InformativeChannel informative;

  NewsAgent agent1;
  agent1.ChangeLocation(&champaign_loc);
  agent1.AddNewsChannelClient(&clickbait);

  NewsAgent agent2;
  agent2.ChangeLocation(&champaign_loc);
  agent2.AddNewsChannelClient(&informative);

  /**
   * You are welcome to add more locations, agents, or channels and experiment
   * with them. The expected output for the given code can be found in the
   * lab assignment on the course website.
   */

  std::cout << "=== EVENT IN CHAMPAIGN ===" << std::endl;
  champaign_loc.Event(
      "02/14/21", "Murphy's", "is selling rose for $2.50 a glass");

  agent1.ChangeLocation(&cypress_loc);

  std::cout << "=== EVENT IN CHAMPAIGN ===" << std::endl;
  champaign_loc.Event("01/04/2021", "The line at Lion", "is not long");

  std::cout << "==== EVENT IN CYPRESS ====" << std::endl;
  cypress_loc.Event("09/01/20",
                    "The University of Houston",
                    "is visiting several local highschools");

  agent1.AddNewsChannelClient(&informative);
  agent1.RemoveNewsChannelClient(&clickbait);

  std::cout << "==== EVENT IN CYPRESS ====" << std::endl;
  cypress_loc.Event("02/15/21", "The greater Houston area", "experiences snow");

  agent2.AddNewsChannelClient(&clickbait);

  std::cout << "=== EVENT IN CHAMPAIGN ===" << std::endl;
  champaign_loc.Event("04/13/21",
                      "Students",
                      "received their third non-instructional break day");
}