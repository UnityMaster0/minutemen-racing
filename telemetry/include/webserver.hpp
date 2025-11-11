#pragma once
#ifndef WEB_SERVER_HPP
#define WEB_SERVER_HPP

#include <WiFi.h>
#include <WebServer.h>
#include <FS.h>
#include <SPIFFS.h>

const char *ssid = "MMR";
const char *password = "password";

WebServer server(80);

void startWiFiAP()
{
    Serial.println();
    Serial.print("Configuring access point...");

    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);

    Serial.print("IP address of the AP: ");
    Serial.println(WiFi.softAPIP());
}

String getContentType(String filename)
{
    if (filename.endsWith(".html"))
        return "text/html";
    if (filename.endsWith(".css"))
        return "text/css";
    if (filename.endsWith(".js"))
        return "application/javascript";
    if (filename.endsWith(".png"))
        return "image/png";
    if (filename.endsWith(".jpg"))
        return "image/jpeg";
    if (filename.endsWith(".gif"))
        return "image/gif";
    if (filename.endsWith(".ico"))
        return "image/x-icon";
    if (filename.endsWith(".json"))
        return "application/json";
    return "text/plain";
}

void serverRouting()
{

    server.on("/", HTTP_GET, []()
              {
                File file = SPIFFS.open("/index.html", "r");
                if (!file) {
                    server.send(404, "text/plain", "File Not Found");
                    return;
                }
                server.streamFile(file, "text/html");
                file.close(); });

    server.on("/data", HTTP_GET, []()
              { server.send(201, "text/plain", readSensors() + "," + getGPSData()); });

    server.onNotFound([]()
                {
                String path = server.uri();

                File file = SPIFFS.open(path, "r");
                if (!file) {
                    server.send(404, "text/plain", "File Not Found");
                    return;
                }

                String contentType = getContentType(path); 
                server.streamFile(file, contentType);
                file.close(); });
}

#endif
