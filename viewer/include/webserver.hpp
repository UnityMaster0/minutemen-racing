#pragma once
#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <ESP8266WebServer.h>
#include <FS.h>

ESP8266WebServer server(80);

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
              {        
                Serial.println('d');
                
                String output;

                delay(80);

                if (Serial.available() > 0)
                {
                    output = Serial.readStringUntil('\n');
                } else {
                    output = "";
                }

                server.send(201, "text/plain", output); });

    server.on("/vcc", HTTP_GET, []()
              {        
                Serial.println('v');
                
                String output;

                delay(80);

                if (Serial.available() > 0)
                {
                    output = Serial.readStringUntil('\n');
                    Serial.println(output);
                } else {
                    output = "";
                }

                server.send(201, "text/plain", output); });
}

#endif