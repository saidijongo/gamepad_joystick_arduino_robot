#include <Arduino.h>

const int rightMotorPositivePin = 5;
const int rightMotorNegativePin = 6;
const int leftMotorPositivePin = 3;
const int leftMotorNegativePin = 4;

const int joystickXPin = A0;
const int joystickYPin = A1;

const int joystickThreshold = 256;

void setup() {
    pinMode(rightMotorPositivePin, OUTPUT);
    pinMode(rightMotorNegativePin, OUTPUT);
    pinMode(leftMotorPositivePin, OUTPUT);
    pinMode(leftMotorNegativePin, OUTPUT);
    pinMode(joystickXPin, INPUT);
    pinMode(joystickYPin, INPUT);
}

void loop() {
    int xPosition = analogRead(joystickXPin) - 512;
    int yPosition = analogRead(joystickYPin) - 512;

    if (abs(yPosition) > joystickThreshold) {
        if (yPosition > 0) {
            motor_forward(leftMotorPositivePin, leftMotorNegativePin);
            motor_forward(rightMotorPositivePin, rightMotorNegativePin);
            delay(50);
        } else {
            motor_backward(leftMotorPositivePin, leftMotorNegativePin);
            motor_backward(rightMotorPositivePin, rightMotorNegativePin);
            delay(50);
        }
    } else if (abs(xPosition) > joystickThreshold) {
        if (xPosition > 0) {
            motor_forward(leftMotorPositivePin, leftMotorNegativePin);
            motor_backward(rightMotorPositivePin, rightMotorNegativePin);
            delay(50);
        } else {
            motor_backward(leftMotorPositivePin, leftMotorNegativePin);
            motor_forward(rightMotorPositivePin, rightMotorNegativePin);
            delay(50);
        }
    }
}

void motor_forward(int positivePin, int negativePin) {
    digitalWrite(positivePin, HIGH);
    digitalWrite(negativePin, LOW);
}

void motor_backward(int positivePin, int negativePin) {
    digitalWrite(positivePin, LOW);
    digitalWrite(negativePin, HIGH);
}
