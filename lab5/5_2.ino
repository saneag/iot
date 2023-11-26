#include <PID_v1.h>
#include <LiquidCrystal_I2C.h>

// Definire pini pentru encoder
const int encoderPinA = 2;
const int encoderPinB = 3;

// Definire pini pentru motor
const int motorPin1 = 4;
const int motorPin2 = 5;

// Definire pini pentru potentiometru
const int potPin = A0;

// Definire pini pentru LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adresă I2C și dimensiuni LCD

// Definire obiect PID
double Setpoint, Input, Output;
PID pid(&Input, &Output, &Setpoint, 1, 0, 0, DIRECT);

void setup()
{
    // Inițializare pini
    pinMode(encoderPinA, INPUT);
    pinMode(encoderPinB, INPUT);
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);

    // Inițializare LCD
    lcd.begin(16, 2);

    // Inițializare PID
    Setpoint = analogRead(potPin); // Setpoint inițial de la potentiometru
    pid.SetMode(AUTOMATIC);
}

void loop()
{
    // Citire valoare encoder
    int encoderValue = readEncoder();

    // Citire valoare potentiometru
    Setpoint = analogRead(potPin);

    // Calculare PID
    Input = encoderValue;
    pid.Compute();

    // Afișare valori pe LCD
    lcd.setCursor(0, 0);
    lcd.print("Setpoint: ");
    lcd.print(Setpoint);

    lcd.setCursor(0, 1);
    lcd.print("Current: ");
    lcd.print(encoderValue);

    // Control motor
    if (Output > 0)
    {
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
    }
    else
    {
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
    }

    // O întârziere mică pentru stabilitate
    delay(50);
}

int readEncoder()
{
    static int oldEncoderValue = 0;
    static int encoderValue = 0;

    // Citire starea pinilor encoder
    int MSB = digitalRead(encoderPinA);
    int LSB = digitalRead(encoderPinB);

    int encoded = (MSB << 1) | LSB;
    int sum = (oldEncoderValue << 2) | encoded;

    // Actualizare valoare encoder
    if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
    {
        encoderValue++;
    }
    else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
    {
        encoderValue--;
    }

    oldEncoderValue = encoded;
    return encoderValue;
}