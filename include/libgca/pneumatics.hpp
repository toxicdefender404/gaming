#pragma once
#include "api.h"
class Pneumatics {
    pros::ADIDigitalOut piston;
    bool state;

    public:
    /**
     * @brief Construct a new Pneumatics object
     * 
     * @param iPort solenoid port
     * @param initState initial state of the piston
     */
    Pneumatics(char iPort, bool initState = false);

    /**
     * @brief Destroys the Pneumatics object
     * 
     */
    ~Pneumatics() = default;

    /**
     * @brief Toggles the solenoid to the value opposite to the current state
     * 
     */
    void toggle();

    /**
     * @brief Sets the state of the solenoid
     * 
     * @param iState state
     */
    void set(bool iState);

    /**
     * @brief Get the State of the cylinder
     * 
     * @return whether the piston is extended 
     */
    bool getState() const;
};