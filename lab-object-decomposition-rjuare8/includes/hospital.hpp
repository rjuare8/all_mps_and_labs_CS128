#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include <set>
#include <string>
#include <vector>

#include "appointment.hpp"
#include "timeslot.hpp"

class Hospital {
public:
  Hospital() = default;
  void AddDoctor(Doctor& d);
  Doctor* GetAvailableDoctor(TimeSlot time);

  void RemoveAppointment(TimeSlot time, std::string patient);
  void AddAppointment(TimeSlot time, std::string patient);

private:
  std::vector<Doctor*> doctors_;
  std::vector<Appointment> appointments_;
};

#endif