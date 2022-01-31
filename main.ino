#include "lcd.h"
#include "microphone.h"
#include "arduino.h"

void setup() {
  // Setup port, LCD, and Accleromter read
  Serial.begin(9600);
  lcdStartup(); 
  while (!Serial);
  accStart();
}

void loop() {
  // Continuously read the microphone to detect if spike is occuring
  readMicrophone();

  // Read the accelerometer, output its measurements onto the serial plotter, and return the magnitude of acceleration
  am = readAcceleration();

  // If the magnitude of accleration exceeds 25, a fall is deemed to have occur
  if(am > 25){
    // Display message on LCd and exit the program
    lcdCountdown();
    exit(0);
    }
  }
}

