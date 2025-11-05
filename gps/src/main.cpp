#include <Arduino.h>

#define GPS_SERIAL Serial2

void setup()
{
  Serial.begin(115200);
  
  GPS_SERIAL.begin(115200);
}

void loop()
{
  Serial.println(GPS_SERIAL.readStringUntil('\n'));
}