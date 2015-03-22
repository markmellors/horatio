#include <NewPing.h>
#include "Servo.h"

// Ultrasonic detection stuff
const int TRIGGER_PIN = 12;
const int ECHO_PIN = 11;
const int MAX_DISTANCE = 50;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

unsigned long firstSeen = 0;
const unsigned long DWELL_TIME = 3000;
boolean isRunning = false;

// Waving
const int NUMBER_OF_WAVES = 3;
int endStopDegrees = 60;
int waveTime = 500;

// Servos
Servo waveServo;
Servo shakeServo;

void setup() {
    Serial.begin(115200);
    waveServo.attach(9);
    waveServo.write(90);
    shakeServo.attach(8);
    shakeServo.write(90);
}

void loop() {
    delay(50);
    int distance = getDistance();
    bool doThings = shouldDoThings(distance);

    // If we have something in range,
    // and we're not already doing so, wave;
    if(doThings){
    int waveOrShake = random(100);
        if (waveOrShake > 50) {
            shake(distance);
            Serial.println("Shake hands");
        } else {
            wave(distance);
            Serial.println("waving");
        }
    }
}

bool shouldDoThings(int distance){
    unsigned long now = millis();

    if(distance > 0){
        // If this is the first time we're seeing a ping
        // Record the time and continue
        if (firstSeen == 0){
            firstSeen = now;
            return false;
        }
        // If more than DWELL_TIME has elapsed with continous
        // pings, then do things

        if ((now - firstSeen) > DWELL_TIME){
            firstSeen = 0;
            return true;
        }

        // Keep on looping
        return false;
    } else {
        // No ping detected. reset firstSeen and return False
        firstSeen = 0;
        return false;
    }
}

int getDistance(){
    int uS = sonar.ping();
    int distance = uS / US_ROUNDTRIP_CM;
    return distance;
}

void reset(){
    waveServo.write(90);
    shakeServo.write(90);
    delay(15);
}

void wave(int uS){
    isRunning = true;
    Serial.print("Distance:");
    Serial.println(uS);
    for (int n=0; n < NUMBER_OF_WAVES; n++){
        waveServo.write(180 - endStopDegrees);
        delay(waveTime);
        waveServo.write(0 + endStopDegrees);
        delay(waveTime);
    }
    waveServo.write(90);
    delay(waveTime);
    isRunning = false;
}

void shake(int uS){
    isRunning = true;
    Serial.print("Distance:");
    Serial.println(uS);
    for (int n=0; n < NUMBER_OF_WAVES; n++){
        shakeServo.write(180 - endStopDegrees);
        delay(waveTime);
        shakeServo.write(0 + endStopDegrees);
        delay(waveTime);
    }
    shakeServo.write(90);
    delay(waveTime);
    isRunning = false;
}
