#include <stdio.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 16, 1);

#define PORT_13 13
#define PORT_12 12

String led_on = "led on";
String led_off = "led off";

void setup() {
  pinMode(PORT_13, OUTPUT);
  pinMode(PORT_12, OUTPUT);
  lcd.backlight();
  lcd.init();
  Serial.begin(9600);
}

void loop() {
  static char userInput[7];
  static char correctCode[7] = { '7', '3', '5', '5', '6', '0', '8' };
  static int count = 0;
  char customKey = customKeypad.getKey();
  String correct = "Correct";
  String wrong = "Wrong";
  bool isCorrect = true;

  if (customKey) {
    lcd.print(customKey);
    Serial.print(customKey);
    digitalWrite(PORT_12, LOW);
    digitalWrite(PORT_13, LOW);

    if (count >= 7) {
      lcd.clear();
      count = 0;
      return;
    }

    if (customKey == 'C') {
      lcd.clear();
      lcd.setCursor(0, 0);
      count = 0;
      return;
    }

    if (count < 7) {
      userInput[count] = customKey;
    }

    count++;

    if (count == 7) {
      for (int i = 0; i < 7; i++) {
        if (userInput[i] != correctCode[i]) {
          isCorrect = false;
          break;
        }
      }

      lcd.clear();

      if (isCorrect) {
        lcd.print(correct);
        digitalWrite(PORT_12, HIGH);
        digitalWrite(PORT_13, LOW);
      } else {
        lcd.print(wrong);
        digitalWrite(PORT_13, HIGH);
        digitalWrite(PORT_12, LOW);
      }
    }
  }

  if (Serial.available()) {
    String input = Serial.readString();

    input.trim();

    if (input == led_on) {
      digitalWrite(PORT_13, HIGH);
      Serial.println(led_on);
    } else if (input == led_off) {
      digitalWrite(PORT_13, LOW);
      Serial.println(led_off);
    } else {
      Serial.println("Invalid input");
    }
  }
}