#include <ESP8266WiFi.h>
const char* ssid = "WIFI_NAME";
const char* password = "WIFI_PASSWORD";
char server[] = "SMTPSERVER";

WiFiClient espClient;
void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("");
  Serial.println("");
  Serial.print("Connecting To: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("*");
  }
  Serial.println("");
  Serial.println("WiFi Connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  byte ret = sendEmail();
 }

void loop()
{
  
}

byte sendEmail()
{
  if (espClient.connect(server, 2525) == 1) 
  {
    Serial.println(F("connected"));
  } 
  else 
  {
    Serial.println(F("connection failed"));
    return 0;
  }
  if (!emailResp()) 
    return 0;

  Serial.println(F("Sending EHLO"));
  espClient.println("EHLO www.example.com");
  if (!emailResp()) 
    return 0;

  Serial.println(F("Sending auth login"));
  espClient.println("AUTH LOGIN");
  if (!emailResp()) 
    return 0;
 
  Serial.println(F("Sending User"));
  
  espClient.println("SMTP_USERNAME");
  if (!emailResp()) 
    return 0;
  Serial.println(F("Sending Password"));
 
  espClient.println("SMTP_PASSWORD");
  if (!emailResp()) 
    return 0;

  Serial.println(F("Sending From"));
  espClient.println(F("MAIL From: SENDER_EMAIL"));
  if (!emailResp()) 
    return 0;

  Serial.println(F("Sending To"));
  espClient.println(F("RCPT To: RECIPIENT_EMAIL"));
  if (!emailResp()) 
    return 0;

  Serial.println(F("Sending DATA"));
  espClient.println(F("DATA"));
  if (!emailResp()) 
    return 0;
  Serial.println(F("Sending email"));

  espClient.println(F("To:  RECIPIENT_EMAIL"));
 
  espClient.println(F("From: SENDER_EMAIL"));
  espClient.println(F("Subject: SUBJECT\r\n"));
  espClient.println(F("TEST\r\n"));
  
  espClient.println(F("."));
  if (!emailResp()) 
    return 0;
  
  Serial.println(F("Sending QUIT"));
  espClient.println(F("QUIT"));
  if (!emailResp()) 
    return 0;
  
  espClient.stop();
  Serial.println(F("disconnected"));
  return 1;
}

byte emailResp()
{
  byte responseCode;
  byte readByte;
  int loopCount = 0;

  while (!espClient.available()) 
  {
    delay(1);
    loopCount++;
   
    if (loopCount > 20000) 
    {
      espClient.stop();
      Serial.println(F("\r\nTimeout"));
      return 0;
    }
  }

  responseCode = espClient.peek();
  while (espClient.available())
  {
    readByte = espClient.read();
    Serial.write(readByte);
  }

  if (responseCode >= '4')
  {
  
    return 0;
  }
  return 1;
}
