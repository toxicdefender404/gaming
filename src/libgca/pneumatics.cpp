#include "main.h"

Pneumatics::Pneumatics(char iPort, bool initState):piston(iPort,initState), state(initState){
    piston.set_value(state);
}

void Pneumatics::toggle(){
    state = !state;
    piston.set_value(state);
}

void Pneumatics::set(bool iState){
    state = iState;
    piston.set_value(iState);
}

bool Pneumatics::getState() const{
    return state;
}