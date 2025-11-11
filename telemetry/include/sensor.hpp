#pragma once
#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <Arduino.h>

#define AFR_POS_PIN A2
#define AFR_NEG_PIN A3
#define RPM_PIN A4
#define TPS_PIN 33
#define IPS_PIN 32

String readSensors() {

    String sensorData;

    // AFR
    sensorData += analogRead(AFR_POS_PIN) - analogRead(AFR_NEG_PIN);
    sensorData += ',';
    
    // RPM
    sensorData += analogRead(RPM_PIN);
    sensorData += ',';
    
    // TPS
    sensorData += analogRead(TPS_PIN);
    sensorData += ',';
    
    // IPS
    sensorData += analogRead(IPS_PIN);

    return sensorData;
}

#endif