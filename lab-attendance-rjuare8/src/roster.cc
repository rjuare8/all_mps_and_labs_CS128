#include "roster.hpp"

#include <iostream>

Roster::Roster(const Student& student) {
  head_ = std::make_unique<RosterEntry>(student, nullptr);
}

void Roster::AddStudent(const Student& student) {
  if (head_ == nullptr) {
    head_ = std::make_unique<RosterEntry>(student, nullptr);
    return;
  }
  std::cout << "test" << std::endl;

  auto* current = head_.get();

  if (current->next == nullptr && student >= current->student) {
    current->next = std::make_unique<RosterEntry>(student, nullptr);
  } else if (current->next == nullptr) {
    std::unique_ptr<RosterEntry> head_new =
        std::make_unique<RosterEntry>(student, nullptr);
    head_new->next = std::move(head_);
    head_ = std::move(head_new);
  } else {
    std::unique_ptr<RosterEntry> in_student =
        std::make_unique<RosterEntry>(student, nullptr);
    while (current->next != nullptr && current->next->student < student) {
      current = current->next.get();
    }

    if (current->next != nullptr) {
      in_student->next = std::move(current->next);
      current->next = std::move(in_student);
    } else {
      current->next = std::move(in_student);
    }
  }
}

Roster::Iterator Roster::begin() const { return Iterator(head_.get()); }

Roster::Iterator Roster::end() const { return Iterator(); }
