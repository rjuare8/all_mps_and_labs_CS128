#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>

class Room {
public:
  Room();
  Room(std::string room_name);
  std::string GetName() const;
  virtual void AddPerson(std::string name);
  virtual void RemovePerson(std::string name);
  const std::vector<std::string>& GetPeople() const;

protected:
  virtual bool CanAddPerson() const = 0;
  std::vector<std::string> people_;

private:
  std::string name_;
};

#endif  // ROOM_HPP