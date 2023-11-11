// Header File
#ifndef PotentiometerRead_h
#define PotentiometerRead_h

#include <Arduino.h>

class PotentiometerRead {
public:
    PotentiometerRead(unsigned int pin, const char* name, unsigned int minVal = 0, unsigned int maxVal = 1023, unsigned long debounceDelayVal = 10, bool reverseDirection = false);
    int readValue();
    void setMinValue(unsigned int minVal);
    unsigned int getMinValue();
    void setMaxValue(unsigned int maxVal);
    unsigned int getMaxValue();
    void setDebounceDelay(unsigned long debounceDelayVal);
    unsigned long getDebounceDelay();

private:
    unsigned int Pin;
    const char* Name;
    unsigned int pMin;
    unsigned int pMax;
    unsigned long debounceDelay;
    bool reverseP_Direction;
    unsigned long lastChangeTime = 0; // Initialize to 0
    unsigned int lastReading = 0; // Initialize to 0
    void updateReading();
};

#endif