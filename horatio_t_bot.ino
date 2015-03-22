#include <NewPing.h>
// Ultrasonic detection stuff
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 50

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

boolean isRunning = false;

void setup() {
    Serial.begin(115200);
}

void loop() {
    delay(50);
    int uS = sonar.ping();
    Serial.print("Ping: ");
    Serial.print(uS / US_ROUNDTRIP_CM);
    Serial.println("cm");
}
