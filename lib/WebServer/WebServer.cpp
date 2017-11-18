#include "WebServer.h"

const char* ssid = "RoboHand";
const char* password = "robohand123";

const char INDEX[] =
"<!DOCTYPE HTML>"
"<html>"
"<head>"
"<title>RoboHand</title>"
"<style> input[type=\"range\"] { position:relative; -webkit-transform: rotate(90deg); top: 100px; margin: -25px;}"
"</style>"
"</head>"
"<body bgcolor=white>"
"<h1>RoboHand</h1>"
"<form action=\"fingers\" method=\"POST\" onchange=\"this.form.submit()\">"
"<input type=\"range\" min=\"0.0\" max=\"1.0\" step=\"0.05\" name=\"finger1\">"
"<input type=\"range\" min=\"0.0\" max=\"1.0\" step=\"0.05\" name=\"finger2\">"
"<input type=\"range\" min=\"0.0\" max=\"1.0\" step=\"0.05\" name=\"finger3\">"
"<input type=\"range\" min=\"0.0\" max=\"1.0\" step=\"0.05\" name=\"finger4\">"
"<input type=\"range\" min=\"0.0\" max=\"1.0\" step=\"0.05\" name=\"finger5\">"
"<br><br><br><br><br><br><br><br><br>"
"<input type=\"submit\" value=\"Submit\">"
"</form>"
"</body>"
"</html>";

ESP8266WebServer WebServer::server;
RoboHand* WebServer::roboHand;

void WebServer::_handleSubmit() {
    if (server.hasArg("finger1")) {
        roboHand->setAngle(0, 1.0 - server.arg("finger1").toFloat());
    }

    if (server.hasArg("finger2")) {
        roboHand->setAngle(1, 1.0 - server.arg("finger2").toFloat());
    }

    if (server.hasArg("finger3")) {
        roboHand->setAngle(2, 1.0 - server.arg("finger3").toFloat());
    }

    if (server.hasArg("finger4")) {
        roboHand->setAngle(3, 1.0 - server.arg("finger4").toFloat());
    }

    if (server.hasArg("finger5")) {
        roboHand->setAngle(4, 1.0 - server.arg("finger5").toFloat());
    }

    server.sendHeader("Location","/");
    server.send(303);
}

void WebServer::_handleRoot() {
    server.send(200, "text/html", INDEX);
}

void WebServer::_handleNotFound() {
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET)?"GET":"POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i=0; i<server.args(); i++){
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}

void WebServer::setRoboHand(RoboHand* roboHand) {
    WebServer::roboHand = roboHand;
}

IPAddress WebServer::initServer() {
    IPAddress Ip(192, 168, 1, 1);
    IPAddress NMask(255, 255, 255, 0);

    WiFi.softAPConfig(Ip, Ip, NMask);
    WiFi.softAP(ssid, password);

    server.on("/", HTTP_GET, WebServer::_handleRoot);
    server.on("/fingers", HTTP_POST, WebServer::_handleSubmit);
    server.onNotFound(WebServer::_handleNotFound);

    server.begin();

    return WiFi.softAPIP();
}

void WebServer::handleClient() {
    server.handleClient();
}