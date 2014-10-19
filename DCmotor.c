#include "DCmotor.h"


// M1 left
// M2 right
void motorInit(){
  // Keep pins low if unused.
  set_outputs(M1reverse, M1enable, 0b0000);
  set_outputs(M2reverse, M2enable, 0b0000);
  set_directions(M1reverse, M1enable, 0b1111);
  set_directions(M2reverse, M2enable, 0b1111);

}  

void motorTest()
{
  motorInit();


  // Start PWM process.  Period 1 ms, Freq 1 kHz
  pwm_start(basepwm);                            
  
  // Turn motors counterclockwise for 3 s.
  high(M1forward);
  high(M2forward);
  pwm_set(M1enable, 0, 1000);
  pwm_set(M2enable, 1, 1000);
  pause(2000);

  // Stop again
  pwm_set(M1enable, 0, 0);
  pwm_set(M2enable, 1, 0);
  
  // End the PWM process
  pwm_stop();   
}  

void moveMotorT(int left, int right, int time)
{
  motorInit();


  // Start PWM process.  Period 1 ms, Freq 1 kHz
  pwm_start(basepwm);                            
  
  if(left >=0){
    high(M1forward);
  }  else {
    high(M1reverse);
    left=abs(left);
  }
   if(right >=0){
    high(M2forward);
  }  else {
    high(M2reverse);
    right=abs(right);
  }
  pwm_set(M1enable, 0, left);
  pwm_set(M2enable, 1, right);
  pause(time);

  // Stop again
  pwm_set(M1enable, 0, 0);
  pwm_set(M2enable, 1, 0);
  
  // End the PWM process
  pwm_stop();   
}  
void moveDistance(int distance)
{
  motorInit();

  // Start PWM process.  Period 1 ms, Freq 1 kHz
  pwm_start(basepwm);                            
  
  // Turn motors counterclockwise for 3 s.
  if(distance >=0){
    high(M1forward);
    high(M2forward);
  }  else {
    high(M1reverse);
    high(M2reverse);
    distance=abs(distance);
  }
  
  pwm_set(M1enable, 0, 1000);
  pwm_set(M2enable, 1, 1000);
  pause(distance);

  // Stop again
  pwm_set(M1enable, 0, 0);
  pwm_set(M2enable, 1, 0);
  
  // End the PWM process
  pwm_stop();   
}  

void moveMotors(int left, int right)
{
  motorInit();

  // Start PWM process.  Period 1 ms, Freq 1 kHz
  pwm_start(basepwm);                            
  
  if(left >=0){
    high(M1forward);
  }  else {
    high(M1reverse);
    left=abs(left);
  }
   if(right >=0){
    high(M2forward);
  }  else {
    high(M2reverse);
    right=abs(right);
  }
  pwm_set(M1enable, 0, left);
  pwm_set(M2enable, 1, right);


}  

void stopMotors()
{
  motorInit();
  // Stop 
  pwm_set(M1enable, 0, 0);
  pwm_set(M2enable, 1, 0);
  
  // End the PWM process
  pwm_stop();   
}  