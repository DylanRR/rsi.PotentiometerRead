#ifndef HALL_EFFECT_POTENTIOMETER_H
#define HALL_EFFECT_POTENTIOMETER_H

#include <Arduino.h>

class HallEffectPotentiometerRead {
public:
  HallEffectPotentiometerRead(unsigned int pin, unsigned int inputVoltage, unsigned int minVoltageRange, unsigned int maxVoltageRange, unsigned int confidenceLevel = 20);
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

  void setHallDirectionalConfidenceLevel(unsigned int hallDirConfidenceLevel);

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

  int hallDirection;
  unsigned int hallDirCount;
  unsigned int hallDirConfidenceLevel;
  unsigned int hallReading;
  bool readingLocked;
};

#endif