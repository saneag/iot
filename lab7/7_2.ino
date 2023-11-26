#inlude < Wire.h>
#include <Servo.h>

#define servo 3

Servo servo;

void doit()
{
    Wire.read();
    servo.write(90);
}

void setup()
{
    Wire.begin(3);
    Wire.onReceive(doit);
    ser.attach(servo);
    ser.write(0);
}

void loop()
{
    ser.write(0);
    delay(500);
}