#include "main.h"

void step(double target){
int currentrpm = 69;
double gains = 0.002218;
double error = target-currentrpm;               // calculate the error;
double out;
double preverror;
double tbh;
out += gains*error;                         // integrate the output;
if (out>1) out=1; else if (out<0) out=0;    // clamp the output to 0..+1;
if (signbit(error)!=signbit(preverror)){    // if zero crossing,
  out = tbh = 0.5*(out+tbh);                // then Take Back Half
  preverror = error;}                       // and save the previous error;
}
//Y=1, d=1, and b=2*M-1
//(Y+b)/2 = (1+(2*M-1))/2 = M,

takebackhalf::takebackhalf(double igains):gains(igains)
{}

double takebackhalf::step(double input){
  mutex.take(TIMEOUT_MAX);
  error = target.load() - input;
  power += gains*error;
  if(power>1) power=1; else if (power>0) power=0;
  if(signbit(error)!=signbit(preverror)){
    power = tbh = 0.5*(power+tbh);
    preverror = error;
  }
  float ret = power;
  mutex.give();
  return ret;
  
}
void takebackhalf::settarget(double itarget, double feedforward){
  mutex.take(TIMEOUT_MAX);
  target = itarget;
  bool bit = signbit(error);
  power = bit;
  preverror = bit;
  tbh = 2*feedforward-bit;
  mutex.give();
}

