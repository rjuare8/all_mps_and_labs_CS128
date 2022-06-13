#include "illini_book.hpp"

#include <fstream>
#include <queue>
#include <set>

// Your code here!

IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  std::ifstream ifs_ppl{people_fpath};
  std::ifstream ifs_path{relations_fpath};
  graph_ = std::map<int, std::map<int, std::string>>();

  int value = 0;
  while (ifs_ppl.good()) {
    ifs_ppl >> value;
    if (ifs_ppl.fail()) {
      ifs_ppl.clear();
      ifs_ppl.ignore(1, '\n');
    } else {
      graph_.insert({value, std::map<int, std::string>()});
    }
  }

  std::string line;
  while (std::getline(ifs_path, line)) {
    graph_ << line;
  }
}

std::map<int, std::map<int, std::string>>& operator<<(
    std::map<int, std::map<int, std::string>>& graph, const std::string& line) {
  size_t idx = 0;

  int uin1 = std::stoi(SubstrFromPosToDel(line, idx));

  int uin2 = std::stoi(SubstrFromPosToDel(line, idx));

  std::string relationship = SubstrFromPosToDel(line, idx);

  graph.at(uin1).insert({uin2, relationship});

  graph.at(uin2).insert({uin1, relationship});

  return graph;
}

std::string SubstrFromPosToDel(const std::string& str, size_t& idx) {
  std::string substr;
  for (; idx < str.size(); idx++) {
    if (str.at(idx) == ',' || str.at(idx) == '\n') break;

    substr.push_back(str.at(idx));
  }
  idx += 1;

  return substr;
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  std::queue<int> tracker;
  std::set<int> visited;

  tracker.push(uin_1);
  visited.insert(uin_1);

  while (!tracker.empty()) {
    if (tracker.front() == uin_2) return true;

    for (auto const& neighbor : graph_.at(tracker.front())) {
      if (visited.find(neighbor.first) == visited.end()) {
        tracker.push(neighbor.first);
        visited.insert(neighbor.first);
      }
    }
    tracker.pop();
  }

  return false;
}

bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) const {
  std::queue<int> tracker;
  std::set<int> visited;

  tracker.push(uin_1);
  visited.insert(uin_1);

  while (!tracker.empty()) {
    if (tracker.front() == uin_2) return true;

    for (auto const& neighbor : graph_.at(tracker.front())) {
      if (visited.find(neighbor.first) == visited.end() &&
          neighbor.second == relationship) {
        tracker.push(neighbor.first);
        visited.insert(neighbor.first);
      }
    }
    tracker.pop();
  }

  return false;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  std::queue<int> tracker;
  std::queue<int> height;
  std::set<int> visited;

  tracker.push(uin_1);
  visited.insert(uin_1);
  height.push(0);

  while (!tracker.empty()) {
    if (tracker.front() == uin_2) return height.front();

    for (auto const& neighbor : graph_.at(tracker.front())) {
      if (visited.find(neighbor.first) == visited.end()) {
        tracker.push(neighbor.first);
        visited.insert(neighbor.first);
        height.push(height.front() + 1);
      }
    }

    height.pop();
    tracker.pop();
  }

  return -1;
}

int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) const {
  std::queue<int> tracker;
  std::queue<int> height;
  std::set<int> visited;

  tracker.push(uin_1);
  visited.insert(uin_1);
  height.push(0);

  while (!tracker.empty()) {
    if (tracker.front() == uin_2) return height.front();

    for (auto const& neighbor : graph_.at(tracker.front())) {
      if (visited.find(neighbor.first) == visited.end() &&
          neighbor.second == relationship) {
        tracker.push(neighbor.first);
        visited.insert(neighbor.first);
        height.push(height.front() + 1);
      }
    }

    height.pop();
    tracker.pop();
  }

  return -1;
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  std::vector<int> steps;
  std::queue<int> tracker;
  std::queue<int> height;
  std::set<int> visited;

  tracker.push(uin);
  visited.insert(uin);
  height.push(0);

  while (!tracker.empty()) {
    if (height.front() == n) steps.push_back(tracker.front());

    for (auto const& neighbor : graph_.at(tracker.front())) {
      if (visited.find(neighbor.first) == visited.end()) {
        tracker.push(neighbor.first);
        visited.insert(neighbor.first);
        height.push(height.front() + 1);
      }
    }

    height.pop();
    tracker.pop();
  }
  return steps;
}

size_t IlliniBook::CountGroups() const {
  std::set<int> visited;
  int count = 0;
  for (auto const& node : graph_) {
    if (visited.find(node.first) == visited.end()) {
      BSF(visited, node.first);
      count++;
    }
  }

  return count;
}

std::set<int>& IlliniBook::BSF(std::set<int>& visited, int node) const {
  std::queue<int> tracker;

  tracker.push(node);
  visited.insert(node);

  while (!tracker.empty()) {
    for (auto const& neighbor : graph_.at(tracker.front())) {
      if (visited.find(neighbor.first) == visited.end()) {
        tracker.push(neighbor.first);
        visited.insert(neighbor.first);
      }
    }
    tracker.pop();
  }
  return visited;
}

size_t IlliniBook::CountGroups(const std::string& relationship) const {
  std::set<int> visited;
  int count = 0;
  for (auto const& node : graph_) {
    if (visited.find(node.first) == visited.end()) {
      BSFwithRelationship(visited, node.first, relationship);
      count++;
    }
  }

  return count;
}

std::set<int>& IlliniBook::BSFwithRelationship(
    std::set<int>& visited, int node, const std::string& relationship) const {
  std::queue<int> tracker;

  tracker.push(node);
  visited.insert(node);

  while (!tracker.empty()) {
    for (auto const& neighbor : graph_.at(tracker.front())) {
      if (visited.find(neighbor.first) == visited.end() &&
          neighbor.second == relationship) {
        tracker.push(neighbor.first);
        visited.insert(neighbor.first);
      }
    }
    tracker.pop();
  }
  return visited;
}

size_t IlliniBook::CountGroups(
    const std::vector<std::string>& relationships) const {
  std::set<int> visited;
  int count = 0;
  for (auto const& node : graph_) {
    if (visited.find(node.first) == visited.end()) {
      BSFwithMulRelationships(visited, node.first, relationships);
      count++;
    }
  }

  return count;
}

std::set<int>& IlliniBook::BSFwithMulRelationships(
    std::set<int>& visited,
    int node,
    const std::vector<std::string>& relationships) const {
  std::queue<int> tracker;

  tracker.push(node);
  visited.insert(node);

  while (!tracker.empty()) {
    for (auto const& neighbor : graph_.at(tracker.front())) {
      if (visited.find(neighbor.first) == visited.end() &&
          Contains(neighbor.second, relationships)) {
        tracker.push(neighbor.first);
        visited.insert(neighbor.first);
      }
    }
    tracker.pop();
  }
  return visited;
}

bool Contains(const std::string& string,
              const std::vector<std::string>& vector) {
  for (auto const& relationship : vector) {
    if (relationship == string) return true;
  }

  return false;
}
