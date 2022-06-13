#include "solution.hpp"

#include <iostream>
#include <queue>
#include <set>

Solution::Solution(
    const std::vector<std::pair<std::string, std::string>>& prerequisites) {
  for (auto const& pair : prerequisites) {
    if (!(VertexInGraph(pair.first))) {
      AddVertex(pair.first);
    }

    GetAdjacencyList(pair.first).push_back(pair.second);
  }
}

int Solution::Solve(const std::string& start, const std::string& dest) {
  std::queue<std::string> tracker;
  std::queue<int> height;
  std::set<std::string> visited;

  tracker.push(start);
  height.push(0);
  visited.insert(start);

  while (!tracker.empty()) {
    std::cout << "current course" << tracker.front() << std::endl;
    std::cout << "current height" << height.front() << std::endl;
    if (tracker.front() == dest) {
      return height.front();
    }

    if (VertexInGraph(tracker.front())) {
      for (auto const& neighbor : GetAdjacencyList(tracker.front())) {
        if (visited.find(neighbor) == visited.end()) {
          tracker.push(neighbor);
          visited.insert(neighbor);
          height.push(height.front() + 1);
        }
      }
    }
    height.pop();
    tracker.pop();
  }

  return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Provide function definitions (uncomment to use!)                          //
///////////////////////////////////////////////////////////////////////////////

void Solution::AddVertex(const std::string& vertex) {
  if (VertexInGraph(vertex))
    throw std::runtime_error("vertex already in graph.");

  adj_.insert({vertex, std::list<std::string>()});
}

std::list<std::string>& Solution::GetAdjacencyList(const std::string& vertex) {
  return adj_.find(vertex)->second;
}

bool Solution::VertexInGraph(const std::string vertex) {
  if (adj_.find(vertex) != adj_.end())
    return true;
  else
    return false;
}

std::ostream& operator<<(std::ostream& os, const Solution& sol) {
  os << "Contents:" << std::endl;

  for (const auto& pair : sol.adj_) {
    os << "  " << pair.first << ": [ ";

    for (const auto& list_entry : pair.second) {
      os << list_entry << " ";
    }

    os << "]" << std::endl;
  }

  return os;
}