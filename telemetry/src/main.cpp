#include "sensor.hpp"
#include "gps.hpp"
#include "webserver.hpp"

#define DEVICE_NAME "MMR"

void setup()
{
    Serial.begin(115200);
    GPS_SERIAL.begin(GPSBaud);
    
    if (!SPIFFS.begin(true))
    {
        Serial.println("SPIFFS Mount Failed");
        return;
    }
    
    startWiFiAP();
    
    server.begin();
    serverRouting();
}

void loop()
{
    server.handleClient();
}