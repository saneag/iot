#include <Wire.h>

#define SENSOR 7

int data;

void setup()
{
    Wire.begin();
    pinMode(SENSOR, INPUT);
}

void loop()
{
    data = digitalRead(SENSOR);
    if (data)
    {
        Wire.beginTransmission(3);
        Wire.write(1);
        Wire.endTransmission();
    }

    delay(200);
}