#pragma once
#include "api.h"
#include "pid.hpp"
#include "pros/imu.hpp"
#include "pros/motors.hpp"
#include <vector>

class Drive{
    std::vector<pros::Motor> leftMotors
    std::vector<pros::Motor> rightMotors
    public:

    PID turnpid;
    PID fwdpid;
    pros::Imu imu
};