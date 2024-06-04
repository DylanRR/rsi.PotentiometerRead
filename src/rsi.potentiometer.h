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
    virtual void updateValue();
    unsigned int getMinValue();
    unsigned int getMaxValue();
    void setMinValue(unsigned int minValue);
    void setMaxValue(unsigned int maxValue);
    void setConfidenceLevel(unsigned int confidenceLevel);
    int checkForChange();

    
protected:
    unsigned int reading;
    unsigned int confidenceLevel;
    unsigned int pin;
    unsigned int confidence = 0;
    unsigned int minValue;
    unsigned int maxValue;
    unsigned int currentReading;
    unsigned int previousReading;
    bool reverseDirection = false;
    unsigned int cfc;
};

/**
 * Polymorphic class for reading a potentiometer using a Hall Effect sensor.
 * @extends PotentiometerRead
*/
class HallEffectPotentiometerRead : public PotentiometerRead {
public:
    HallEffectPotentiometerRead(unsigned int pin, unsigned int minValue = 0, unsigned int maxValue = 1023, unsigned int confidenceLevel = 20, int directionalDeltaConfidence = 3, bool reverseDirection = false);
    void updateValue() override;
    void setDirectionalDeltaConfidence(int directionalDeltaConfidence);
    int getDirectionalDeltaConfidence();

private:
    int directionalDeltaConfidence;
    unsigned int hallDirection;
    int hallDirCount;
};

#endif
