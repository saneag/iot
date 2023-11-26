#include <stdio.h>

#define northRedPin 2
#define northYellowPin 3
#define northGreenPin 4
#define eastRedPin 5
#define eastYellowPin 6
#define eastGreenPin 7

#define northPin 8
#define eastPin 9

struct State
{
    int Out;
    int Time;
    int Next[4];
}

typedef const struct State SType;

#define goSouth 0
#define waitSouth 1

#define goWest 2
#define waitWest 3

SType FSM[4] = {
    {0b100001, 300, {goSouth, waitSouth, goSouth, waitSouth}},
    {0b100010, 300, {goWest, goWest, goWest, goWest}},
    {0b001100, 300, {goWest, goWest, waitWest, waitWest}},
    {0b010100, 300, {goSouth, goSouth, goSouth, goSouth}}};

int pinState;

void setup()
{
    pinMode(northRedPin, OUTPUT);
    pinMode(northYellowPin, OUTPUT);
    pinMode(northGreenPin, OUTPUT);
    pinMode(eastRedPin, OUTPUT);
    pinMode(eastYellowPin, OUTPUT);
    pinMode(eastGreenPin, OUTPUT);
    pinMode(northPin, INPUT);
    pinMode(eastPin, INPUT);
    pinState = goSouth;
}

void loop()
{
    int output = FSM[pinState].Out;
    SetOutput(output);
    delay(FSM[pinState].Time);
    int input = GetInput();
    pinState = FSM[pinState].Next[input];
}

int GetInput(void)
{
    int northButton = digitalRead(northPin);
    int eastButton = digitalRead(eastPin);
    if (northButton && eastButton)
        return 0b11;
    else if (northButton)
        return 0b10;
    else if (eastButton)
        return 0b01;
    else
        return 0b00;
}

int SetOutput(int out)
{
    int ledState;
    ledState = (out & (1 << 5)) ? HIGH : LOW;
    digitalWrite(eastRedPin, ledState);

    ledState = (out & (1 << 4)) ? HIGH : LOW;
    digitalWrite(eastYellowPin, ledState);

    ledState = (out & (1 << 3)) ? HIGH : LOW;
    digitalWrite(eastGreenPin, ledState);

    ledState = (out & (1 << 2)) ? HIGH : LOW;
    digitalWrite(northRedPin, ledState);

    ledState = (out & (1 << 1)) ? HIGH : LOW;
    digitalWrite(northYellowPin, ledState);

    ledState = (out & (1 << 0)) ? HIGH : LOW;
    digitalWrite(northGreenPin, ledState);
}