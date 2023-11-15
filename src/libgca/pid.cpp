#include "libgca/pid.hpp"


void PID::reset_variables() {
  output = 0;
  target = 0;
  error = 0;
  prev_error = 0;
  integral = 0;
  time = 0;
  prev_time = 0;
}

PID::PID() {
  reset_variables();
  set_constants(0, 0, 0, 0);
}
