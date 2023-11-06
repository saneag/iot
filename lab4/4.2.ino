#include <Stepper.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int stepsPerRevolution = 2038;

Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  if (Serial.available()) {
    int rotSpeed = Serial.parseInt();
    if (rotSpeed != 0) {
      Serial.println(rotSpeed);
      myStepper.setSpeed(abs(rotSpeed));
      if (rotSpeed > 0) {
        lcd.clear();
        lcd.print("Forward");
        myStepper.step(stepsPerRevolution);
      } else if (rotSpeed < 0) {
        lcd.clear();
        lcd.print("Backward");
        myStepper.step(-stepsPerRevolution);
      }
    }
  }
}