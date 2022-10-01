//MSFDD Email Sender - Sends email when fall is detected

#include <ESP8266WiFi.h>
const char* ssid = "________"; //network ssid
const char* password = "________"; //network password
char server[] = "________"; //smtp servername, which is used for the email send protocol

WiFiClient espClient;

//Setup is code that is run once on Arduino
void setup()
{
  Serial.begin(115200); 
  delay(10);
  WiFi.begin(ssid, password); //Start wifi connection, logging in with wifi username and password

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print("Waiting..."); //Prints 'Waiting...' when connection has not been established yet
  }
  byte ret = sendEmail(); //stores email function result in byte code
 }

//Empty as there is no looping process, simply one send protocol to smtp server
void loop()
{
  
}

//Email send function
byte sendEmail() 
{
  if (espClient.connect(server, 2525) != 1) //Cheecks if connection to server at port 2525 is successful, if not return
    return 0;
  if (!emailResponse())  //Checks result of calling email response function, this function servers, called
    return 0;			 //called in between operations to ensure successful completion of process
  espClient.println("EHLO ________"); //SMTP domain name is used for authorization by WIFIClient library
  if (!emailResponse()) 
    return 0;
  espClient.println("AUTH LOGIN"); //Command triggers client to request credentials for smtp account
  if (!emailResponse()) 
    return 0;
  espClient.println("________"); //Sending SMTP Username
  if (!emailResponse()) 
    return 0;
  espClient.println("________"); //Sending SMTP Password
  if (!emailResponse()) 
    return 0;
  espClient.println(F("MAIL From: ________")); //Mail address that will appear as sender
  if (!emailResponse()) 
    return 0;
  espClient.println(F("RCPT To: ________")); //Recipient email address
  if (!emailResponse()) 
    return 0;
  espClient.println(F("DATA")); //DATA command enables next information lines sent to client to be the body of the email
  if (!emailResponse()) 
    return 0;

//Email ody
  espClient.println(F("To:  ________"));
  espClient.println(F("From: ________"));
  espClient.println(F("Subject: ________\r\n")); // \r\n designates end of first 3 fields
  espClient.println(F("Your loved one has fallen. Please attend to them or go to emergency services!\r\n"));  //msg
  espClient.println(F("."));
  if (!emailResponse()) 
    return 0;
  espClient.println(F("QUIT")); //Quit command ends the email
  if (!emailResponse()) 
    return 0;
  espClient.stop(); //Stops sending client
  return 1; //email sent if return value is 1
}

byte emailResponse()
{
  byte rCode; //code for response
  byte readByteEm; //documented read byte
  int waitTime = 0; //counter to check how long there is no response

  while (!espClient.available()) //Loop checking status of response, in this case inactive
  {
    delay(1); //run every ms
    waitTime++; //increment wait time ctr
    if (waitTime > 30000) //If there is no response for 30s, end client
    {
      espClient.stop();
      return 0;
    }
  }

  rCode = espClient.peek(); //retrieves response code from client
  
  while (espClient.available()) //Loop checking status of response, in this case active
  {
    readByteEm = espClient.read(); //read byte from client
    Serial.write(readByteEm); //write byte to srial
  }
  if (rCode >= '4') //fail code
  {
    return 0;
  }
  return 1; //If successful it will be 1 and allow protocol
}
