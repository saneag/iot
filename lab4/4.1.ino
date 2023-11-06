#include <LiquidCrystal_I2C.h>

#define RELAY 12

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  pinMode(RELAY, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  if(Serial.available()) {
    String read = Serial.readString();
    read.trim();

    if(read == "on") {
      lcd.clear();
      digitalWrite(RELAY, HIGH);
      Serial.println("Led is on");
      lcd.print("Led is on");
    } else if(read == "off") {
      lcd.clear();
      digitalWrite(RELAY, LOW);
      Serial.println("Led is off");
      lcd.print("Led is off");
    } else {
      lcd.clear();
      Serial.println("Invalid input");
      lcd.print("Invalid input");
    }
  }
}