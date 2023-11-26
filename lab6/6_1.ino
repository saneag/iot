#include <stdio.h>

#define ledPin 13
#define buttonPin 2

#define LED_OFF_STATE 0
#define LED_ON_STATE 1

struct State
{
    unsigned long OUT;
    unsigned long Time;
    unsigned long Next[2];
}

typedef const struct State SType;

SType FSM[2] = {
    {0, 10, {LED_OFF_STATE, LED_ON_STATE}}, {1, 10, {LED_ON_STATE, LED_OFF_STATE}}};

int FSM_State = LED_OFF_STATE;

void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT);
    FSM_State = LED_OFF_STATE;
}

void loop()
{
    int output = FSM[FSM_State].OUT;
    digitalWrite(ledPin, output);
    int input = digitalRead(buttonPin);
    FSM_State = FSM[FSM_State].Next[input];
}