#include <ESP8266WiFi.h>
#include "Gsender.h"

const char* ssid = "ssidname";                   // Your WIFI network name
const char* password = "strongpassword";         // Your WIFI network password
uint8_t connection_state = 0;
uint16_t reconnect_interval = 10000;
char temp;
String command;

uint8_t WiFiConnect(const char* nSSID = nullptr, const char* nPassword = nullptr)
{
  static uint16_t attempt = 0;
  Serial.print("Connecting to ");
  if (nSSID) {
    WiFi.begin(nSSID, nPassword);
    Serial.println(nSSID);
  } else {
    WiFi.begin(ssid, password);
    Serial.println(ssid);
  }

  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 50)
  {
    delay(200);
    Serial.print(".");
  }
  ++attempt;
  Serial.println("");
  if (i == 51) {
    Serial.print("Connection: TIMEOUT on attempt: ");
    Serial.println(attempt);
    if (attempt % 2 == 0)
      Serial.println("Check if access point available \r\n");
    return false;
  }
  Serial.println("Connection: ESTABLISHED");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  return true;
}

void Awaits()
{
  uint32_t ts = millis();
  while (!connection_state)
  {
    delay(50);
    if (millis() > (ts + reconnect_interval) && !connection_state) {
      connection_state = WiFiConnect();
      ts = millis();
    }
  }
}

void setup()
{
  Serial.begin(115200);
  connection_state = WiFiConnect();
  if (!connection_state) // If it is not connected to the specify WIFI network it will constantly try to connect
    Awaits();
}

void loop() {
  if (Serial.available() > 0)
  {
    command = "";
  }
  while (Serial.available() > 0)
  {
    temp = ((byte)Serial.read());
    command += temp;
    delay(1);
  }
  if (command == "send") {
    sendAlertMail();
    command = "";
  }
}

void sendAlertMail() {
  Gsender *gsender = Gsender::Instance();
  String subject = "Sample notification message";
  if (gsender->Subject(subject)->Send("destinationEmail@gmail.com", "Your loved one has fallen!\nPlease contact authorities and/or visit them.\nPlease dismiss this message if it was a false alarm.\n")) {
    Serial.println("Message sent.");
  } else {
    Serial.print("Error sending message: ");
    Serial.println(gsender->getError());
  }
}
