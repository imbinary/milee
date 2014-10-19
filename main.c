/*
robot control by chris 
*/
#include "simpletools.h"                      // Include simple tools
#include "xbee.h"
#include "pixy/pixy.h"
#include "main.h"
#include "ping.h" 
#include "DCmotor.h"
#include "LSM303.h"
#include "sensors.h"

/*
 *pin0  M1 en
 *pin1  M1 in1  
 *pin2  M1 in2
 *pin3  
 *pin4  rng T
 *pin5  rng E
 *pin6  xbee CTS'
 *pin7  xbee RTS'
 *pin8  xbee di
 *pin9  xbee do
 *pin10 M2 en
 *pin11 M2 in1
 *pin12 M2 in2
 *pin13 pxy in
 *pin14 pxy out
 *pin15 pxy clk
 */


int *pixy_cog; 
int *lsm303_cog;
int *serial_start; 

extern volatile lsm303AccelData accelData;    // Last read accelerometer data will be available here
extern volatile lsm303MagData magData;        // Last read magnetometer data will be available here
extern volatile uint16_t blockCount;

int main()
{
  int running=1;
  xbeeinit();
  dprint(xbee,"\ninit...\n");
  pixy_cog = cog_run(&pixyStart, 60); 
  lsm303_cog = cog_run(&lsm303_start, 30);
//  serial_start = cog_run(&serialstart, 30);
  //if(!lsm303_begin()){
  // dprint(xbee,"accel init...failed\n"); ;
  //}    

  
  dprint(xbee,"command: ");
  while(running)
  {       
    pause(500);
   
    if( fdserial_rxReady(xbee) )sgets();
    
   

  } 
  cog_end(pixy_cog); 
  cog_end(lsm303_cog);
  print("done...\n"); 
}

