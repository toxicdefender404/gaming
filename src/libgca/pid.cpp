#include "libgca/pid.hpp"
#include <cmath>


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

PID::Constants PID::get_constants() { return constants; }

void PID::set_constants(double p, double i, double d, double p_start_i) {
  constants.kp = p;
  constants.ki = i;
  constants.kd = d;
  constants.start_i = p_start_i;
}

PID::PID(double p, double i, double d, double start_i){
  reset_variables();
  set_constants(p, i, d, start_i);
}

void PID::set_exit_condition(int small_exit_time, double small_error, int big_exit_time, double big_error, int velocity_exit_time) {
  exit.small_exit_time = small_exit_time;
  exit.small_error = small_error;
  exit.big_exit_time = big_exit_time;
  exit.big_error = big_error;
  exit.velocity_exit_time = velocity_exit_time;
}


void PID::reset_timers() {
  smalltime = 0;
  bigtime = 0;
  veltime = 0;
}

double PID::step(double current) {
  error = target - current;
  derivative = error - prev_error;

  if (constants.ki != 0) {

    if (fabs(error) < constants.start_i){
      integral += error;
    }
    if (std::signbit(error) != std::signbit(prev_error)){
      integral = 0;
    }
  }

  output = error * constants.kp + integral * constants.ki + derivative * constants.kd;

  prev_error = error;


  if (std::abs(error) < exit.small_error) {  
    smalltime += 10;
    bigtime = 0;
      if (smalltime > exit.small_exit_time) {
        reset_timers();
        settled = true;
      }
    } 

  else {
      smalltime = 0;
    }

  if (std::abs(error) < exit.big_error) {
    bigtime += 10;
    if (bigtime > exit.big_exit_time) {
      reset_timers();
      settled = true;
    }
  } 
  else {
    bigtime = 0;
  }

  if (std::abs(derivative) <= 0.05) {
    veltime += 10;
      if (veltime > exit.velocity_exit_time) {
        reset_timers();
        settled = true;
      }
    } 
  else {
    veltime = 0;
  }

  return output;
}

void PID::set_target(double input){
  target = input;
  settled = false;
}
double PID::get_target(){
  return target;
}