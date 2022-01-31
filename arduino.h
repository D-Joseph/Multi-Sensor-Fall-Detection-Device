#include <Arduino_LSM6DS3.h>

void accStart(){
  // Continue trying to establish connection with the acceleromter if you cannot in the beginning
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

int readAcceleration(){
  float ax, ay, az;
  // Check to see if sensor is receiving input
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);
    // The raw magnitude of acceleration is calculated using sqrt(ax^2 + ay^2 + az^2)
    // Multiply this value by 10 to make it easier to view on output, and also to seperate it visually from the components of acceleration
    float magAccleration = pow(pow(ax,2)+pow(ay,2)+pow(az,2),0.5) * 10;

    // Add serial plotter output
    Serial.print("ax: "); Serial.print(ax);
    Serial.print(" | ay: "); Serial.print(ay);
    Serial.print(" | az: "); Serial.print(az);
    Serial.print(" | |a|: "); Serial.print(am);
    Serial.println("");
  
  // Used for fall detection
  return magAccleration;
}