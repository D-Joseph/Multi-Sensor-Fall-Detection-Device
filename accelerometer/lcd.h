#include "LiquidCrystal.h"
// Initialize pins for the lcd

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void lcdStartup(){
    // Initialize lcd to display nothing
    lcd.begin(16, 2);
    lcd.clear();
}

void lcdCountdown(){
    // If a fall has been detected, then start the countdown sequence
    int16_t count = 9;
    do{
        lcd.setCursor(0, 0); lcd.print("Fall Detected, ");
        lcd.setCursor(0, 1); lcd.print("Notifying in: ");
        lcd.setCursor(14,1); lcd.print(count); //Print current timer value on the LCD
        lcd.setCursor(15, 1); lcd.print("s"); 
        count--; // Decrement count variable
        delay(1000); // Set a delay every second
    }while(count > 0); // Continue doing while count is greater than 0
    lcd.clear(); //Wipes LCD of any previous text
    lcd.setCursor(0,0); 
    lcd.print("Message Sent To");
    lcd.setCursor(0,1); 
    lcd.print("Emerg. Contacts");
}
