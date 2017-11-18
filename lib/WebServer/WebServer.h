#ifndef WebServer_h
#define WebServer_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <RoboHand.h>

class WebServer {
public:
    static void setRoboHand(RoboHand*);
    static IPAddress initServer();
    static void handleClient();
private:
    static ESP8266WebServer server;
    static RoboHand* roboHand;

    static void _handleRoot();
    static void _handleSubmit();
    static void _handleNotFound();
    WebServer() {};
};

#endif