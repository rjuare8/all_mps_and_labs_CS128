#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <map>
#include <set>
#include <string>
#include <vector>

class IlliniBook {
public:
  IlliniBook(const std::string& people_fpath,
             const std::string& relations_fpath);
  IlliniBook(const IlliniBook& rhs) = delete;
  IlliniBook& operator=(const IlliniBook& rhs) = delete;
  ~IlliniBook() = default;
  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string& relationship) const;
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string& relationship) const;
  std::vector<int> GetSteps(int uin, int n) const;

  size_t CountGroups() const;
  size_t CountGroups(const std::string& relationship) const;
  size_t CountGroups(const std::vector<std::string>& relationships) const;

private:
  std::set<int>& BSFwithRelationship(std::set<int>& visited,
                                     int node,
                                     const std::string& relationship) const;
  std::set<int>& BSFwithMulRelationships(
      std::set<int>& visited,
      int node,
      const std::vector<std::string>& relationship) const;
  std::set<int>& BSF(std::set<int>& visited, int node) const;
  std::map<int, std::map<int, std::string>>
      graph_;  // students as key and map of
               // students and relationship as value
};

std::string SubstrFromPosToDel(const std::string& str, size_t& idx);
std::map<int, std::map<int, std::string>>& operator<<(
    std::map<int, std::map<int, std::string>>& graph, const std::string& line);

bool Contains(const std::string& string,
              const std::vector<std::string>& vector);

#endif
