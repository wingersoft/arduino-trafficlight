#include <Arduino.h>

// Traffic Light Simulation with State Machine for Two Lights
// 5 States: Light1 Green/Light2 Red, Light1 Yellow/Light2 Red, Light1 Red/Light2 Green, Light1 Red/Light2 Yellow, All Red
// Light 1: Pins 13,12,11 | Light 2: Pins 10,9,8

enum TrafficState
{
    LIGHT1_GREEN_LIGHT2_RED,
    LIGHT1_YELLOW_LIGHT2_RED,
    LIGHT1_RED_LIGHT2_GREEN,
    LIGHT1_RED_LIGHT2_YELLOW,
    ALL_RED
};

const int redPin1 = 13;
const int yellowPin1 = 12;
const int greenPin1 = 11;
const int redPin2 = 10;
const int yellowPin2 = 9;
const int greenPin2 = 8;

TrafficState currentState = LIGHT1_RED_LIGHT2_GREEN;
unsigned long previousMillis = 0;
const unsigned long redDuration = 30000;    // 30 seconds
const unsigned long greenDuration = 30000;  // 30 seconds
const unsigned long yellowDuration = 5000;  // 5 seconds

void setup()
{
    pinMode(redPin1, OUTPUT);
    pinMode(yellowPin1, OUTPUT);
    pinMode(greenPin1, OUTPUT);
    pinMode(redPin2, OUTPUT);
    pinMode(yellowPin2, OUTPUT);
    pinMode(greenPin2, OUTPUT);

    // Start with light 1 red, light 2 green
    digitalWrite(redPin1, HIGH);
    digitalWrite(yellowPin1, LOW);
    digitalWrite(greenPin1, LOW);
    digitalWrite(redPin2, LOW);
    digitalWrite(yellowPin2, LOW);
    digitalWrite(greenPin2, HIGH);
}

void loop()
{
    unsigned long currentMillis = millis();

    switch (currentState)
    {
        case LIGHT1_RED_LIGHT2_GREEN:
            if (currentMillis - previousMillis >= greenDuration)
            {
                // Transition to LIGHT1_RED_LIGHT2_YELLOW
                digitalWrite(greenPin2, LOW);
                digitalWrite(yellowPin2, HIGH);
                currentState = LIGHT1_RED_LIGHT2_YELLOW;
                previousMillis = currentMillis;
            }
            break;

        case LIGHT1_RED_LIGHT2_YELLOW:
            if (currentMillis - previousMillis >= yellowDuration)
            {
                // Transition to ALL_RED
                digitalWrite(yellowPin2, LOW);
                digitalWrite(redPin2, HIGH);
                currentState = ALL_RED;
                previousMillis = currentMillis;
            }
            break;

        case ALL_RED:
            if (currentMillis - previousMillis >= 2000)  // 2 second all red
            {
                // Transition to LIGHT1_GREEN_LIGHT2_RED
                digitalWrite(redPin1, LOW);
                digitalWrite(greenPin1, HIGH);
                currentState = LIGHT1_GREEN_LIGHT2_RED;
                previousMillis = currentMillis;
            }
            break;

        case LIGHT1_GREEN_LIGHT2_RED:
            if (currentMillis - previousMillis >= greenDuration)
            {
                // Transition to LIGHT1_YELLOW_LIGHT2_RED
                digitalWrite(greenPin1, LOW);
                digitalWrite(yellowPin1, HIGH);
                currentState = LIGHT1_YELLOW_LIGHT2_RED;
                previousMillis = currentMillis;
            }
            break;

        case LIGHT1_YELLOW_LIGHT2_RED:
            if (currentMillis - previousMillis >= yellowDuration)
            {
                // Transition to LIGHT1_RED_LIGHT2_GREEN
                digitalWrite(yellowPin1, LOW);
                digitalWrite(redPin1, HIGH);
                digitalWrite(redPin2, LOW);
                digitalWrite(greenPin2, HIGH);
                currentState = LIGHT1_RED_LIGHT2_GREEN;
                previousMillis = currentMillis;
            }
            break;
    }
}