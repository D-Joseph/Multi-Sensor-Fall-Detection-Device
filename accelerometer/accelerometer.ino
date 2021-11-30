#include <Arduino_LSM6DS3.h>
#include "lcd.h"

int micPrev = 511;
int spike = 0;

void setup() {
  Serial.begin(9600);
  lcdStartup();
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }
}

void loop() {
  readMicrophone();
  float ax, ay, az;
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);
    float rAM = pow(pow(ax,2)+pow(ay,2)+pow(az,2),0.5);
  int am = rAM * 10;
  // Multiply the value by 10 to make it easier to read on the serial plotter
  // and to seperate it visually from the components of acceleration
  // Serial.print("ax: "); Serial.print(ax);
  // Serial.print(" | ay: "); Serial.print(ay);
  // Serial.print(" | az: "); Serial.print(az);
  // Serial.print(" | |a|: "); Serial.print(am);
  // Serial.println("");

  if(am > 25){
    lcdCountdown();
    exit(0);
    }
  }
}

void readMicrophone(){ /* function readMicrophone */
 ////Test routine for Microphone
 int micVal = analogRead(A0);
 if ((micPrev + 300) < micVal || (micPrev - 300) > micVal) spike = 200;
 Serial.print(F("Mic: ")); Serial.println((String)micVal+" "+(String)spike);
 spike = 0;
 micPrev = micVal;
}
