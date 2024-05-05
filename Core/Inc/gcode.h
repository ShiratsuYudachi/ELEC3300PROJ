#ifndef __GCODE_H
#define __GCODE_H 	
const float gcodeCenterOfMass[3] = {26.27919610046221, 24.59985277268477, 26.406016969609617};
const int gcodeLength = 15;
const float gcode[15][4] = {{0.0, 0.0, 0.0, 600},
 {50.0, 0.0, 0.0, 600},
 {50.0, 50.0, 0.0, 600},
 {0.0, 50.0, 0.0, 600},
 {25.0, 25.0, 100.0, 600},
 {50.0, 0.0, 0.0, 600},
 {50.0, 50.0, 0.0, 600},
 {25.0, 25.0, 100.0, 600},
 {0.0, 0.0, 0.0, 600},
 {0.0, 50.0, 0.0, 600},
 {25.0, 50.0, 0.0, 600},
 {25.0, 0.0, 0.0, 600},
 {35.0, 15.0, 0.0, 600},
 {25.0, 0.0, 0.0, 600},
 {15.0, 15.0, 0.0, 600}};
#endif