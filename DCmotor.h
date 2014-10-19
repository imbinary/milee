#include "simpletools.h"  
#define M1enable  0
#define M1forward 1
#define M1reverse 2
#define M2enable  10
#define M2forward 11
#define M2reverse 12
#define basepwm 1000 
void motorTest();
void motorInit();
void moveDistance(int distance);
void moveMotorT(int left, int right, int time);
void moveMotors(int left, int right);
void stopMotors();
