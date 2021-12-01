#include <ArduinoSTL.h>
#include <ESP_Mail_Client.h>
#include <WiFiNINA.h>

#define STMP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

#define AUTHOR_EMAIL "msfddalerts@gmail.com"
#define AUTHOR_PASSWORD "ECE.C.03"
#define RECIPIENT_EMAIL "msfddalerts@gmail.com"

SMTPSession smtp;

void smtpCallback(SMTP_Status status);


char ssid[] = "ARRIS-F91D";
char pass[] = "212507734667";

int status = WL_IDLE_STATUS;


WiFiClient client;

void setup() {

  Serial.begin(9600);

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  smtp.debug(1);

  smtp.callback(smtpCallback);

  ESP_Mail_Session session;

  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  SMTP_Message message;

  message.sender.name = "ESP";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "ESP Test Email";
  message.addRecipient("TESTREC", RECIPIENT_EMAIL);

  String htmlMsg = "<div style=\"color:#2f4468;\"><h1>MSFDD ALERT</h1><p>Your loved one has fallen.</p></div>";
  message.html.content = htmlMsg.c_str();
  message.html.content = htmlMsg.c_str();
  message.text.charSet = "us-ascii";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  if (!smtp.connect(&session))
    return;

  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error: " + smtp.errorReason());

  
}

void loop() {
  
}


void smtpCallback(SMTP_Status status){
  Serial.println(status.info());

  if (status.success()){
    Serial.println("----------------");
    ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
    ESP_MAIL_PRINTF("Message sent failled: %d\n", status.failedCount());
    Serial.println("----------------\n");
    struct tm dt;

    for (size_t i = 0; i < smtp.sendingResult.size(); i++){
   
      SMTP_Result result = smtp.sendingResult.getItem(i);
      time_t ts = (time_t)result.timestamp;
      localtime_r(&ts, &dt);

      ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
      ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
      ESP_MAIL_PRINTF("Date/Time: %d/%d/%d %d:%d:%d\n", dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday, dt.tm_hour, dt.tm_min, dt.tm_sec);
      ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients);
      ESP_MAIL_PRINTF("Subject: %s\n", result.subject);
    }
    Serial.println("----------------\n");
  }
}
