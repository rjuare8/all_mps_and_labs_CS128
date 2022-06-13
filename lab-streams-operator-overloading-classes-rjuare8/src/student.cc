#include "student.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "course.hpp"

Student::Student(std::string name, std::string uin, std::string net_id):
    name_(name),
    uin_(uin),
    net_id_(net_id),
    major_("Undeclared"),
    graduated_(false) {}

Student::Student(std::string name,
                 std::string uin,
                 std::string net_id,
                 std::string major,
                 std::vector<Course> courses,
                 bool graduated):
    name_(name),
    uin_(uin),
    net_id_(net_id),
    major_(major),
    graduated_(graduated),
    courses_(courses) {}

std::string Student::GetName() const { return name_; }

std::string Student::GetUIN() const { return uin_; }

std::string Student::GetNetId() const { return net_id_; }

std::string Student::GetMajor() const { return major_; }

bool Student::HasGraduated() const { return graduated_; }

const std::vector<Course>& Student::GetCourses() const { return courses_; }

void Student::SetName(std::string name) { name_ = name; }

void Student::SetMajor(std::string major) { major_ = major; }

bool Student::AddCourse(Course c) {
  for (Course& taken : courses_) {
    if (taken.name == c.name && taken.credits == c.credits) {
      return false;
    }
  }
  courses_.push_back(c);
  return true;
}

void Student::Graduate() {
  int credits = 0;
  for (Course& taken : courses_) {
    credits += taken.credits;
  }
  if (credits >= min_credits_grad_) {
    graduated_ = true;
  }
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
  int credits = 0;
  std::string courses_taken;
  std::string graduated;

  for (const Course& taken : s.GetCourses()) {
    credits += taken.credits;
    courses_taken += taken.name + ", ";
  }
  if (!courses_taken.empty()) {
    courses_taken.pop_back();
    courses_taken.pop_back();
  }

  if (s.HasGraduated()) {
    graduated = "True";
  } else {
    graduated = "False";
  }

  os << "Name: " << s.GetName() << "\n";
  os << "UIN: " << s.GetUIN() << "\n";
  os << "Net Id: " << s.GetNetId() << "\n";
  os << "Major: " << s.GetMajor() << "\n";
  os << "Credits: " << credits << "\n";
  os << "Courses: " << courses_taken << "\n";
  os << "Graduated: " << graduated;
  return os;
}
