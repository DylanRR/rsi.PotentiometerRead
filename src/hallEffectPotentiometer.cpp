#include "hallEffectPotentiometer.h"
#include <limits.h>
/** Constructor for the PotentiometerRead class.
 * @param pin The pin the potentiometer is connected to
 * @param minValue The minimum value of the potentiometer. (Default = 0)
 * @param maxValue The maximum value of the potentiometer. (Default = 1023)
 * @param confidenceLevel The confidence level of the potentiometer. (Default = 20)
 * @param reverseDirection Whether or not the potentiometer is reversed. (Default = false)
 */
HallEffectPotentiometerRead::HallEffectPotentiometerRead(unsigned int pin, unsigned int inputVoltage = 5, unsigned int minVoltageRange = 0, unsigned int maxVoltageRange = 5, unsigned int confidenceLevel = 20){
  this->pin = pin;
  this->minValue = 0;
  this->maxValue = 1023;
  this->minVoltage = minVoltageRange;
  this->maxVoltage = maxVoltageRange;
  this->inputVoltage = inputVoltage;
  _calcVoltageValues();
  this->confidenceLevel = confidenceLevel;
  this->hallDirection = 0;
  this->hallDirCount = 0;
  this->hallDirConfidenceLevel = 2;
  this->currentReading = 100;
  this->previousReading = -100;
  this->reading = 0;

  pinMode(this->pin, INPUT);

  while(currentReading != previousReading){
    updateValue();
  }
  this->cfc = readValue();
}

/**
 * Method to read the potentiometer.
 * @return The currently updated value of the potentiometer.
 */
unsigned int HallEffectPotentiometerRead::readValue(){
  return reading;
}

/**
 * Method to reset the potentiometer, and get an accurate reading.
 */
void HallEffectPotentiometerRead::reset(){
  this->currentReading = 100;
  this->previousReading = -100;
  while(currentReading != previousReading){
    updateValue();
  }
}

/** Method to set the minimum value of the potentiometer. And reset the previous reading.
 * @param minValue The minimum value
 */
void HallEffectPotentiometerRead::setMinValue(unsigned int minValue) {
  this->minValue = minValue;
  this->previousReading = -100;
  reset();
}

/**
 * Method to get the minimum value
 * @return The minimum value
 */
unsigned int HallEffectPotentiometerRead::getMinValue() {
  return this->minValue;
}

/**
 * Method to set the maximum value of the potentiometer. And reset the previous reading.
 * @param maxValue The maximum value
 */
void HallEffectPotentiometerRead::setMaxValue(unsigned int maxValue) {
  this->maxValue = maxValue;
  this->previousReading = -100;
  reset();
}

/**
 * Method to set the voltage range of the potentiometer. And reset the previous reading.
 * @param minVoltage The minimum voltage
 * @param maxVoltage The maximum voltage
 */
void HallEffectPotentiometerRead::setVoltageRange(float inputVoltage, float minVoltage, float maxVoltage){
    this->inputVoltage = inputVoltage;
    this->minVoltage = minVoltage;
    this->maxVoltage = maxVoltage;
    _calcVoltageValues();
    reset();
}

/**
 * Method to get the maximum value of the potentiometer.
 * @return The maximum value
 */
unsigned int HallEffectPotentiometerRead::getMaxValue() {
  return this->maxValue;
}

/**
 * Method to set the confidence level of the potentiometer.
 * @param confidenceLevel The confidence level
 */
void HallEffectPotentiometerRead::setConfidenceLevel(unsigned int confidenceLevel){
    this->confidenceLevel = confidenceLevel;
}

/**
 * Method to check for a change in the potentiometer.
 * @return The value of the potentiometer if it has changed, otherwise -1.
 */
int HallEffectPotentiometerRead::checkForChange(){
  updateValue();
  if(this->reading > INT_MAX) {
    return -1; // Handle the error: reading is too large to be represented as an int
    Serial.println("PotentiometerRead Class Error: reading is too large to be represented as an int");
  }

  if(this->cfc != this->reading){
    this->cfc = this->reading;
    return this->cfc;
  }
  return -1;
}


/**
 * Method to calculate the minimum voltage value of the potentiometer.
 * @return The minimum voltage value
 */
void HallEffectPotentiometerRead::_calcVoltageValues(){
  this->minVoltageValue = round((this->minVoltage / this->inputVoltage) * 1023);
  this->maxVoltageValue = round((this->maxVoltage / this->inputVoltage) * 1023);
}


void HallEffectPotentiometerRead::setHallDirectionalConfidenceLevel(unsigned int hallDirConfidenceLevel){
  this->hallDirConfidenceLevel = hallDirConfidenceLevel;
}


void HallEffectPotentiometerRead::updateValue(){
  currentReading = analogRead(pin);

  if(currentReading != previousReading){
    confidence++;
  } else {
    confidence = 0;
  }

  if(confidence >= confidenceLevel){
    confidence = 0;

    bool isIncreasing = previousReading > currentReading;
    if (hallDirection == isIncreasing && hallDirCount >= hallDirConfidenceLevel) {
                if (isIncreasing && reading != minValue) {
                    reading--;
                } else if (!isIncreasing && reading != maxValue) {
                    reading++;
                }
            } else if (hallDirection == isIncreasing) {
                hallDirCount++;
            } else {
                hallDirection = isIncreasing;
                hallDirCount = 0;
            }
    previousReading = currentReading;
  }
}