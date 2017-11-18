#include <Arduino.h>
#include <RoboHand.h>

#define WAIT 1000

RoboHand roboHand(D1, D2, D3, D4, D5);

void setup() {
    roboHand.reset();
    Serial.begin(9600);
    Serial.println("Initialized!");    
    delay(1000);
}

void loop() {
    for (int i = 0; i < 5; ++i) {
        roboHand.stretch(i);
        Serial.printf("Stretching %d finger\n", i);
        delay(WAIT);

        roboHand.pull(i);
        Serial.printf("Pulling %d finger\n", i);
        delay(WAIT);
    }

}