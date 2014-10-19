#ifndef _XBEE_H
#define _XBEE_H
#include "simpletools.h"                      // Include simple tools
#include "simplei2c.h"
#include "fdserial.h"
fdserial *xbee;
//fdserial *term;
char response[10];
int serialrun;
int xbcmd(char *cmd, char *reply, int bytesMax, int msMax);
void serialCom();
void xbeeinit();
void serialstart();
void serial_poll();
void sgets();
void doCommand(char command[255]);
#endif
