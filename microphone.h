void readMicrophone(){ 
  // Recieve the sensor input
 int micVal = analogRead(A0);

 // Spike checking is a comparison based on current input to the last reading
 if ((micPrev + 300) < micVal || (micPrev - 300) > micVal) spike = 200; // Display a spike on the graph to show when it occured
 Serial.print(F("Mic: ")); Serial.println((String)micVal+" "+(String)spike); 
 spike = 0; // Reset spike
 micPrev = micVal; // Change previous reading to the new reading
}
