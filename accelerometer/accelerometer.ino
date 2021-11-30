#include "Wire.h"
#include "lcd.h"

const int MPU_addr=0x68;  
int16_t AcX,AcY,AcZ; // Initialize variables for the accelerations components
float ax=0, ay=0, az=0;

void mpu_read(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // Starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,6,true);  // Request 6 registers to read from
  AcX=Wire.read()<<8|Wire.read(); 
  AcY=Wire.read()<<8|Wire.read(); 
  AcZ=Wire.read()<<8|Wire.read();  
 }

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  lcdStartup();
  
}
void loop(){
  mpu_read();

  // Define calibration values
  float xC;
  
  
  ax = (AcX-2050)/16384.00 + .19;
  ay = (AcY-77)/16384.00 -.01;
  az = (AcZ-1947)/16384.00 -1.62;

 // Calculate the magnitude of the user's acceleration
  float rAM = pow(pow(ax,2)+pow(ay,2)+pow(az,2),0.5);
  int am = rAM * 10;
  // Multiply the value by 10 to make it easier to read on the serial plotter
  // and to seperate it visually from the components of acceleration
  Serial.print("ax: "); Serial.print(ax);
  Serial.print(" | ay: "); Serial.print(ay);
  Serial.print(" | az: "); Serial.print(az);
  Serial.print(" | |a|: "); Serial.print(am);
  Serial.println("");

  if(am > 25){
    lcdCountdown();
    exit(0);
  }
}
