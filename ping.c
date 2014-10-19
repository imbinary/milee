#include "simpletools.h"

int ping(int ipin,int opin)
{
  low(ipin);
  pulse_out(ipin, 10);
  return pulse_in(opin, 1);
}

int ping_cm(int ipin,int opin)
{
  long tEcho = ping(ipin,opin);
  int cmDist = tEcho / 58;
  return cmDist;
}

int ping_inches(int ipin,int opin) 
{
  long tEcho = ping(ipin,opin);
  int inDist = tEcho / 148;
  return inDist;
}

void ping_LED(int cmDist)
{
     if(cmDist>25)
      cmDist=25;
    cmDist=cmDist*10;
    dac_ctr(27,1,cmDist); 
}  