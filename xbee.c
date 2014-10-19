
/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/

#include "xbee.h"
#include "DCmotor.h"
#include "string.h"
#include "pixy/pixy.h"
#include "ping.h" 
#include "LSM303.h"
#include "sensors.h"

extern volatile lsm303AccelData accelData;    // Last read accelerometer data will be available here
extern volatile lsm303MagData magData;        // Last read magnetometer data will be available here
extern volatile uint16_t blockCount;

// begin serial

void serialstart()
{
    xbee = fdserial_open(9, 8, 0, 9600);
    serialrun=1;
    while(serialrun)
    {
      serial_poll();
    }    
    
}  


void xbeeinit()
{
  xbee = fdserial_open(9, 8, 0, 9600);
 // simpleterm_close();
 // term = fdserial_open(31,30,0,115200);
  
 
}  

void sgets()
{
    int size = 255;
    char b[size],c=0;
    int i=0;   
    b[0]=NULL;
      while(c != -1 && i<size && c != 13 && c != 10)
      {    
          c = fdserial_rxChar(xbee);
          b[i]=c; 
          //dprint(xbee,"%d ",c);  
          i++;   
      }
      b[i-1]=NULL;
      if(b[0]=='+')
        doCommand(b);
      
      dprint(xbee,"\ncommand: ");
  
}  

void serial_poll()
{
    char c,d;
    
     if(fdserial_rxReady(xbee)){  
      c = fdserial_rxChar(xbee);
      if(c != -1)
      {
        //dprint(xbee, "You typed: %c\n", c);
      }
   }
}  
  
void serialCom()
{
    char c,d;
    writeChar(xbee, CLS);
    dprint(xbee, "Click this terminal, \n");
    dprint(xbee, "and type on keyboard...\n\n");
    
     if(fdserial_rxReady(xbee)){  
      c = fdserial_rxChar(xbee);
      if(c != -1)
      {
        dprint(xbee, "You typed: %c\n", c);
       // dprint(term, "They typed: %c\n", c);
      }
   }
   
}

void doCommand(char command[255])
{
     dprint (xbee,"\n%s",command);
     switch(command[1]){
       
       case 'm': //motor commands        
        if(!processMove(command))dprint(xbee,"\ninvalid command");              
       break;
             
       case 'd': //show sonic distance
        dprint(xbee,"\nDist: %d\n", ping_cm(4,5));           // Display distance
       break;
       
       case 'h': //compass heading
        dprint(xbee,"\nHeading: %d\n",(int)magData.orientation);
       break;
       
       case 'p': //pixy
         if(blockCount){
          for(int i=0;i<blockCount;i++)
            dprint(xbee,"\nPixy: block #%d sig(%d) x(%d) y(%d)\n",i+1,blocks[i].signature,blocks[i].x,blocks[i].y);       
          }  
       break;
       
       case 's': //status
       break;
       
     }        
 
}   
  
   //lsm303_accel_read();
    //dprint(xbee,"accel: %d %d %d\n",(int)(accelData.x*0.001F*9.8F),(int)(accelData.y*0.001F*9.8F),(int)(accelData.z*0.001F*9.8F));
    //lsm303_mag_read();
    //dprint(xbee,"mag: %d %d %d\n",(int)magData.x,(int)(magData.y),(int)(magData.z));
//    if(fdserial_rxReady(term)){        
//      d = fdserial_rxChar(term);
//       if(d != -1)
//      {
//        dprint(xbee, "They typed: %c\n", d);
//       dprint(term, "You typed: %c\n", d);
//      }
//    }      



// issue commands to xbee
//
//
//
int xbcmd(char *cmd, char *reply, int bytesMax, int msMax)
{
  int c = -1, n = 0;
  writeStr(xbee, cmd);
  memset(reply, 0, bytesMax);

  int tmax = (CLKFREQ/1000) * msMax;
  int tmark = CNT;

  while(1)
  {
    c = fdserial_rxCheck(xbee);
    if(c != -1)
      reply[n++] = c;
    if(CNT - tmark > tmax)
      return 0;
    if(c == '\r')
      return n;
  }
}

int processMove(char command[255])
{
    char * pch;
    char * mdata[5]; 
    int i=0;
    //dprint (xbee,"\npre token %s",command);
    //tokenise
    pch = strtok (command," +");
    for (i=0;pch != NULL && i<5;i++)
    {       
      //mdata[i] = strdup(pch);
      strcpy(mdata[i],pch);
      pch = strtok (NULL, " +");
    }
    int left ;
    int right ;
    //dprint (xbee,"\nprocessing");
    //return 1;
    switch(command[2]){
       
       case 'd': //move distance      
          ;
          int dist = atoi(mdata[1]);
          if(dist !=0)moveDistance(dist);
          else return 0;             
       break;
             
       case 't': //move time
          ;
          left = atoi(mdata[1]);
          right = atoi(mdata[2]);
          int time = atoi(mdata[3]);
          if(time !=0)moveMotorT(left,right,time);
          else return 0;
       break;
       
       case 'm': //move motors
          ;
          left = atoi(mdata[1]);
          right = atoi(mdata[2]);
          moveMotors(left,right);
       break;
       
       case 's': //stop
          stopMotors();
       break;
       
     }
   //dprint (xbee,"\nprocessed %s",command);        
   return 1; 
   
}  