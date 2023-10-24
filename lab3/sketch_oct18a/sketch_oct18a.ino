#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 12
#define DHTTYPE DHT11
#define VRX_PIN A0
#define VRY_PIN A1
#define VOLTAGE_REFERENCE 5.0
#define ADC_RESOLUTION 1023.0

int xValue = 0;
int yValue = 0;
int lastXValue = 0;
int lastYValue = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  Serial.begin(9600);
  dht.begin();
}

float ADCtoVoltage(int adcValue) {
  return (adcValue / ADC_RESOLUTION) * VOLTAGE_REFERENCE;
}

int filterSaltAndPepper(int currentValue, int lastValue) {
  if (abs(currentValue - lastValue) > 100) {
    return lastValue;
  }
  return currentValue;
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(dht.readTemperature()) + " C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: " + String(dht.readHumidity()) + " %");

  int rawXValue = analogRead(VRX_PIN);
  int rawYValue = analogRead(VRY_PIN);

  xValue = filterSaltAndPepper(rawXValue, lastXValue);
  yValue = filterSaltAndPepper(rawYValue, lastYValue);

  float xVoltage = ADCtoVoltage(xValue);
  float yVoltage = ADCtoVoltage(yValue);

  float xPercentage = (xValue / ADC_RESOLUTION) * 100;
  float yPercentage = (yValue / ADC_RESOLUTION) * 100;

  Serial.print("x = ");
  Serial.print(xValue);
  Serial.print(" (");
  Serial.print(xVoltage);
  Serial.print("V, ");
  Serial.print(xPercentage);
  Serial.println("%)");

  Serial.print("y = ");
  Serial.print(yValue);
  Serial.print(" (");
  Serial.print(yVoltage);
  Serial.print("V, ");
  Serial.print(yPercentage);
  Serial.println("%)");

  lastXValue = xValue;
  lastYValue = yValue;

  delay(1000);
}
