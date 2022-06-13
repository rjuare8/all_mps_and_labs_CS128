#ifndef SCHEDULE_HPP
#define SCHEDULE_HPP

#include <set>
#include <string>
#include <vector>

// include "appointment.hpp"
//#include "doctor.hpp"
#include "timeslot.hpp"

class Schedule {
public:
  Schedule() = default;
  void MarkAvailable(TimeSlot time);
  void MarkBusy(TimeSlot time);
  bool IsAvailable(TimeSlot time) const;

private:
  std::set<TimeSlot> times_;
};

#endif