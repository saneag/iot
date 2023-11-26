#include <Arduino.h>
#include <stdio.h>

int celsius = 0;
int my_celsius;
int adc;
int Temp_H = 30;
int Temp_L = 20;
int motor = 8;

void setup()
{
    pinMode(A0, INPUT);
    Serial.begin(9600);

    pinMode(2, OUTPUT);
    pinMode(motor, OUTPUT);
}

void loop()
{

    // you can select to use celsius or my_celsius
    celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);

    my_celsius = ((((float)analogRead(A0) / 1024.0) * 5) - 0.5) * 100;

    adc = analogRead(A0);
    Serial.print(adc);
    Serial.println(" adc ");

    Serial.print(celsius);
    Serial.print(" C, ");

    Serial.print(my_celsius);
    Serial.print(" my_celsius C, ");

    if (celsius > Temp_H)
    {
        digitalWrite(motor, HIGH);
        digitalWrite(2, HIGH);
    }

    if (celsius < Temp_L)
    {
        digitalWrite(motor, LOW);
        digitalWrite(2, LOW);
    }

    delay(1000);
}