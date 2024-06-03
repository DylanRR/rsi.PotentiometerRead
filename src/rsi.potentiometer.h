/**
 * PotentiometerRead.h - Library header file for reading a potentiometer.
 * Created By: DylanRR, 11/21/2023
 *
 * For Documentation and usage, see rsi.potentiometer.cpp
 */
#ifndef PotentiometerRead_h
#define PotentiometerRead_h
#include <Arduino.h>
class PotentiometerRead {
public:
    PotentiometerRead(unsigned int pin, unsigned int minValue = 0, unsigned int maxValue = 1023, unsigned int confidenceLevel = 20, bool reverseDirection = false);
    unsigned int readValue();
    void reset();
    void updateValue();
    unsigned int getMinValue();
    unsigned int getMaxValue();
    void setMinValue(unsigned int minValue);
    void setMaxValue(unsigned int maxValue);
    void setVoltageRange(float inputVoltage, float minVoltage, float maxVoltage);
    void setConfidenceLevel(unsigned int confidenceLevel);
    int checkForChange();
private:
    void _calcVoltageValues();
    unsigned int reading;
    unsigned int confidenceLevel;
    unsigned int pin;
    unsigned int confidence = 0;
    unsigned int minValue;
    unsigned int maxValue;
    float inputVoltage;
    float minVoltage;
    float maxVoltage;
    int minVoltageValue;
    int maxVoltageValue;
    unsigned int currentReading;
    unsigned int previousReading;
    bool reverseDirection = false;
    unsigned int cfc;
};
#endif
