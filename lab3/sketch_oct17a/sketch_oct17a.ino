#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 12
#define DHTTYPE DHT11

#define VRX_PIN A0
#define VRY_PIN A1

int xValue = 0;
int yValue = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
  
DHT dht(DHTPIN, DHTTYPE);
  
void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  Serial.begin(9600);
  dht.begin();
}
  
void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(dht.readTemperature()) + " C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: " + String(dht.readHumidity()) + " %");

  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);

  Serial.print("x = ");
  Serial.println(xValue);
  Serial.print("y = ");
  Serial.println(yValue);

  delay(1000);
}