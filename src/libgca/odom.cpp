#include <cmath>
#include "main.h"

pros::ADIEncoder trackl('a','b');
pros::ADIEncoder trackm('c','d');
pros::ADIEncoder trackr('e','f');


//current angle divided by expected angle = width multiplier
constexpr long double WHEELDIA = 2.75;
constexpr long double Lwidth = 4.55408568;
constexpr long double Mwidth = 4.5;
constexpr long double Rwidth  = 4.55408568;

constexpr long double trackwidth = Rwidth + Lwidth;
constexpr long double anglemulti = (WHEELDIA/2)/trackwidth;

// inches/tick (diam*pi)/360
const long double Lratio = 0.02399827721492203; 
const long double Mratio = 0.02399827721492203; 
const long double Rratio = 0.02399827721492203;
const long double radtodeg = 180/okapi::pi;
const long double degtorad = okapi::pi/180;


long double prevl = 0;
long double prevm = 0;
long double prevr = 0;

long double resetorientation;
long double resetradorientation;
long double orientation; 
long double prevorientation = 0;


long double absglobalX;
long double absglobalY;


long double angle360(long double angle) { //makes an angle between 0 and 360
  while(!(angle >= 0 && angle < 360)) {
    if( angle < 0 ) { angle += 360; }
    if(angle >= 360) { angle -= 360; }
  }
  return(angle);
}

long double angle180(long double angle) { // makes an angle between -180 and 180
  while(!(angle >= -180 && angle < 180)) {
    if( angle < -180 ) { angle += 360; }
    if(angle >= 180) { angle -= 360; }
  }
  return(angle);
}



void step(){
  //calc distance wheels moved
  long double currentL = trackl.get_value()*Lratio; 
  long double currentM = trackm.get_value()*Mratio;
  long double currentR = trackr.get_value()*Rratio;

  long double deltal = currentL - prevl;
  long double deltam = currentM - prevm;
  long double deltar = currentR - prevr;

  //calc orientation based on difference between left and right
  orientation = resetradorientation + (currentL-currentR)/trackwidth;
  long double deltaA = orientation - prevorientation;

  long double localX;
  long double localY;

  //calc local offset
  if (deltaA == 0){//prevent divide by zero
    localX = deltam;
    localY = deltar;
  }else{
    long double i = 2*sin(deltaA/2);
    localX = i*((deltam/deltaA)+Mwidth);
    localY = i*((deltar/deltaA)+Rwidth);
  }
  
  long double localpolarangle = 0;
  long double polarradius = 0;

  //converts to polar
  if (!(localX==0&&localY==0)){//prevents divide by zero
    localpolarangle = atan2(localY,localX);
    polarradius = sqrt(pow(localX,2)+pow(localY,2));
  }
  //calculate global offset
  long double globalpolarangle = localpolarangle - prevorientation - (deltaA/2);

  //convert to cartesian
  long double offsetX = polarradius*cos(globalpolarangle); 
  long double offsetY = polarradius*sin(globalpolarangle); 

  //adds offset to previous pos
  absglobalX += offsetX;
  absglobalY += offsetY;

  //updates previous variables
  prevl = currentL;
  prevm = currentM; 
  prevr = currentR;

  prevorientation = orientation;

}

void starttracking(long double o){
  resetorientation = o;
  resetradorientation = o*degtorad;
  trackl.reset();
  trackm.reset();
  trackr.reset();
  while(true){
    step();
  }
}

long double getorientation(){
  return resetorientation + anglemulti * (trackl.get_value()-trackr.get_value());
}