#include "simpletools.h" 
#include "LSM303.h"
#include "sensors.h"

i2c *eeBus;
int lsm303run = 1;


void lsm303_start(){
  if(!lsm303_begin())return;
  lsm303_setMagGain(LSM303_MAGGAIN_1_3);
  while(lsm303run)
  {
    lsm303_poll();
  }    
}  


void lsm303_stop(){
  lsm303run=0;
  pause(1000);
  
}  

void lsm303_poll(){
  lsm303_mag_read();
  lsm303_accel_read();
  
}  

int lsm303_heading(){
  float heading = atan2(magData.x/ _lsm303Mag_Gauss_LSB_XY * SENSORS_GAUSS_TO_MICROTESLA,magData.y/ _lsm303Mag_Gauss_LSB_XY * SENSORS_GAUSS_TO_MICROTESLA)*180 / Pi ;
    if(heading<0)heading+=360;
    return (int)heading;
}  

int lsm303_begin()
{
  eeBus = i2c_newbus(6, 7, 0);
  // Enable the accelerometer
  lsm303_write8(LSM303_ADDRESS_ACCEL, LSM303_REGISTER_ACCEL_CTRL_REG1_A, 0x57);
  uint8_t reg1_a = lsm303_read8(LSM303_ADDRESS_ACCEL, LSM303_REGISTER_ACCEL_CTRL_REG1_A);
  if (reg1_a != 0x57)
  {
    return 0;
  }  
  // Enable the magnetometer
  lsm303_write8(LSM303_ADDRESS_MAG, LSM303_REGISTER_MAG_MR_REG_M, 0x00);

  return 1;
}

void lsm303_mag_read()
{
  char value[7];
  uint8_t xlo = value[0];
  uint8_t xhi = value[1];
  uint8_t ylo = value[2];
  uint8_t yhi = value[3];
  uint8_t zlo = value[4];
  uint8_t zhi = value[5];
  
  // Read the magnetometer
  i2c_in(eeBus,(char)LSM303_ADDRESS_MAG,LSM303_REGISTER_MAG_OUT_X_H_M,1,value,6);


  // Note high before low (different than accel)  
  xhi = value[0];
  xlo = value[1];
  zhi = value[2];
  zlo = value[3];
  yhi = value[4];
  ylo = value[5];
  
  // Shift values to create properly formed integer (low byte first)
  magData.x = (int16_t)(xlo | (xhi << 8));
  magData.y = (int16_t)(ylo | (yhi << 8));
  magData.z = (int16_t)(zlo | (zhi << 8));  
  
  // ToDo: Calculate orientation
  magData.orientation = atan2(magData.x / _lsm303Mag_Gauss_LSB_XY * SENSORS_GAUSS_TO_MICROTESLA,magData.y / _lsm303Mag_Gauss_LSB_XY * SENSORS_GAUSS_TO_MICROTESLA)* 180 / Pi ;
  if(magData.orientation<0)magData.orientation+=360;
}

void lsm303_accel_read()
{
  char value[7];
  // Read the accelerometer
  i2c_in(eeBus,(char)LSM303_ADDRESS_ACCEL,LSM303_REGISTER_ACCEL_OUT_X_L_A|0x80 ,1 ,value,6);


  uint8_t xlo = value[0];
  uint8_t xhi = value[1];
  uint8_t ylo = value[2];
  uint8_t yhi = value[3];
  uint8_t zlo = value[4];
  uint8_t zhi = value[5];

  // Shift values to create properly formed integer (low byte first)
  accelData.x = (int16_t)(xlo | (xhi << 8)) >> 4;
  accelData.y = (int16_t)(ylo | (yhi << 8)) >> 4;
  accelData.z = (int16_t)(zlo | (zhi << 8)) >> 4;
  

}

void lsm303_setMagGain(lsm303MagGain gain)
{
  lsm303_write8(LSM303_ADDRESS_MAG, LSM303_REGISTER_MAG_CRB_REG_M, (char)gain);
}

/***************************************************************************
 PRIVATE FUNCTIONS
 ***************************************************************************/
void lsm303_write8(char address, char reg, char value)
{
  i2c_out(eeBus,address,reg,1,&value,1);
}

char lsm303_read8(char address, char reg)
{
  char value;
  i2c_in(eeBus,address,reg,1,&value,1);

  return value;
}