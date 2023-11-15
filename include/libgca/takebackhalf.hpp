#pragma once
#include "api.h"
#include <atomic>

class takebackhalf {
    std::atomic<double> target{};
    pros::Mutex mutex;
    double error;
    double preverror;
    double tbh;
    double gains;

    public:

    double power;
    /**
     * @brief Construct a new takebackhalf controller
     * 
     * @param igains controller gains
     */
    takebackhalf(double igains);

    /**
     * @brief sets the target of the controller
     * 
     * @param itarget target
     * 
     * @param feedforward the estimated power
     */ 
    void settarget(double itarget,double feedforward);
    double step(double input);
};
