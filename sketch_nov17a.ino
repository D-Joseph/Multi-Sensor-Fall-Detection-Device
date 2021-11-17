//Parameters
const int micPin = A0;
//Variables
int micVal = 0;
int micHigh = 0;
int micPrev = 511;
bool micDetected = false;
bool spike = false;
void setup(){
 //Init Serial USB
 Serial.begin(9600);
 Serial.println(F("Initialize  System"));
 //Init Microphone
 pinMode(micPin, INPUT);
}
void loop(){
 readMicrophone();
}
void readMicrophone(){ /* function readMicrophone */
 ////Test routine for Microphone
 micVal = analogRead(micPin);
 if (micVal > micHigh) micHigh = micVal;
 if (micVal > 600) micDetected = true;
 if ((micPrev + 300) < micVal || (micPrev - 300) > micVal) spike = true;
 Serial.print(F("Mic: ")); Serial.println((String)micVal+" "+(String)micHigh+" "+(String)micDetected+" "+(String)spike);
 micDetected = false;
 spike = false;
 micPrev = micVal;
}
