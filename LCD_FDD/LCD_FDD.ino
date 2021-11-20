#include <LiquidCrystal.h>
//initialize interface pins on LCD
const int d4 = 5, d5 = 4, d6 = 3, d7 = 2, en = 11, rs == 12; 
LiquidCrystal lcd (d4, d5, d6, d7, en, rs);
int countdown = 30; //30 second timer

void setup() {
  lcd.begin(16,2); //16 x 2 (columns x rows)
  lcd.setCursor(0, 0); //Positions cursor on first column and row
  lcd.print("Fall Detected, ");
  lcd.setCursor(0, 1); //positions cursor on first column and second row
  lcd.print("Notifying: ");
}

void loop() {
    if (countdown == 0) {
      lcd.clear() //Wipes LCD with any previous text
      lcd.setCursor(0,0); //Positions cursor on first column and row
      lcd.print("Elderly people");
      lcd.setCursor(0,1); //Positions cursor on first column and second row
      lcd.print("Fall too much!");
  } else {
      lcd.setCursor(12,1); //Positions cursor on twelveth column and second row
      lcd.print("%d s", countdown); //Print current timer value on the LCD
      countdown--; //Decrement countdown variable
  }
  delay(1000); //Wait for a second
}
