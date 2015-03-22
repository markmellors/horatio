#include <NewPing.h>
#include "Servo.h"

// Ultrasonic detection stuff
const int TRIGGER_PIN = 12;
const int ECHO_PIN = 11;
const int MAX_DISTANCE = 50;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

boolean isWaving = false;

// Waving
const int NUMBER_OF_WAVES = 3;
int endStopDegrees = 30;
int waveTime = 500;

// Servos
Servo myservo;

void setup() {
    Serial.begin(115200);
    myservo.attach(9);
    myservo.write(90);
}

void loop() {
    delay(50);
    int distance = getDistance();

    // If we have something in range,
    // and we're not already doing so, wave;
    if (!isWaving && distance > 0) {
        isWaving = true;
        Serial.print("waving");
        Serial.println(distance);
        wave(distance);
        isWaving = false;
    }
}

int getDistance(){
    int uS = sonar.ping();
    int distance = uS / US_ROUNDTRIP_CM;
    return distance;
}

void wave(int uS){
    isWaving = true;
    Serial.print("Distance:");
    Serial.println(uS);
    for (int n=0; n < NUMBER_OF_WAVES; n++){
        myservo.write(180 - endStopDegrees);
        delay(waveTime);
        myservo.write(0 + endStopDegrees);
        delay(waveTime);
    }
    myservo.write(90);
    delay(waveTime);
    isWaving = false;
}
