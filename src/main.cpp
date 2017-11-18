#include <Arduino.h>
#include <RoboHand.h>
#include <WebServer.h>

#define WAIT 1000`

RoboHand roboHand(D1, D2, D3, D4, D5);

void setup() {
    WebServer::setRoboHand(&roboHand);
    roboHand.reset();

    Serial.begin(9600);
    Serial.println();
    Serial.print("IP: ");
    Serial.println(WebServer::initServer());
    Serial.println("Initialized!");    
    delay(1000);
}

void loop() {
    WebServer::handleClient();
}