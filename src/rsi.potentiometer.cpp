/**
 * 
 * PotentiometerRead.cpp - Library source file for reading a potentiometer.
 * Created By: DylanRR, 11/21/2023
 *
 * 
 * This library is designed to read values from a potentiometer.
 * 
 * To use this library, you need to:
 * 
 * 1. Include the "rsi.potentiometer.h" header file in your sketch.
 * 
 * 2. Create an instance of the PotentiometerRead class, passing the pin number where the potentiometer is connected as a parameter to the constructor. 
 *    You can also optionally pass the minimum and maximum values of the potentiometer (default values are 0 and 1023), the confidence level (default is 20), 
 *    and a boolean indicating whether the potentiometer direction is reversed (default is false).
 * 
 *    Example: PotentiometerRead potentiometer(A0);
 * 
 * 3. There are a few ways of reading the potentiometer.
 *       A. You can use the `readValue` method to read the last confident reading of the potentiometer.
 *          Note: This does not check for a new reading, and will return the last confident reading.
 * 
 *          Example: int reading = potentiometer.readValue();
 * 
 *       B. You can use the `updateValue` method in conjunction with `readValue` to update the value of the potentiometer, before reading it. 
 *          This will check if the potentiometer has been moved, and if it has, it will increment the confidence of a change. 
 *          If the confidence of a change is greater than the confidence level you set (default is 0), it will set the reading.
 *          This is useful if you want to update and read the potentiometer in your main loop, and not bog down the loop getting a confident reading every time.
 * 
 *          Example:  potentiometer.updateValue();
 *                    int reading = potentiometer.readValue();
 * 
 *       C. You can use the `reset` method to reset the potentiometer, and get an accurate reading immediately.
 *          This is useful if you need to get an accurate reading every time the loop fires, note that this may slightly bog down the loop, due to the fact
 *          that it will wait until it has a confident reading of the potentiometer before returning.
 *       
 *          Example: potentiometer.reset();
 *                   int reading = potentiometer.readValue();
 * 
 * 4. You can also set and get the minimum and maximum values of the potentiometer using the `setMinValue`, `setMaxValue`, `getMinValue`, and `getMaxValue` methods.
 *    Note that setting the minimum and maximum values will reset the potentiometer, and get an accurate reading immediately.
 *    Example: potentiometer.setMinValue(0);
 *             potentiometer.setMaxValue(1023);
 *             int min = potentiometer.getMinValue();
 *             int max = potentiometer.getMaxValue();
 */

#include "rsi.potentiometer.h"
#include <limits.h>

/** Constructor for the PotentiometerRead class.
 * @param pin The pin the potentiometer is connected to
 * @param minValue The minimum value of the potentiometer. (Default = 0)
 * @param maxValue The maximum value of the potentiometer. (Default = 1023)
 * @param confidenceLevel The confidence level of the potentiometer. (Default = 20)
 * @param reverseDirection Whether or not the potentiometer is reversed. (Default = false)
 */
PotentiometerRead::PotentiometerRead(unsigned int pin, unsigned int minValue, unsigned int maxValue, unsigned int confidenceLevel, bool reverseDirection){
    this->pin = pin;
    this->minValue = minValue;
    this->maxValue = maxValue;
    this->confidenceLevel = confidenceLevel;
    this->currentReading = 100;
    this->previousReading = -100;
    this->reverseDirection = reverseDirection;

    pinMode(this->pin, INPUT);

    reset();
    this->cfc = readValue();
}

/**
 * Method to read the potentiometer.
 * @return The currently updated value of the potentiometer.
 */
unsigned int PotentiometerRead::readValue(){
  return reading;
}

/**
 * Method to reset the potentiometer, and get an accurate reading.
 */
void PotentiometerRead::reset(){
  this->currentReading = 100;
  this->previousReading = -100;
  while(currentReading != previousReading)
    updateValue();
}

/** Method to set the minimum value of the potentiometer. And reset the previous reading.
 * @param minValue The minimum value
 */
void PotentiometerRead::setMinValue(unsigned int minValue) {
  this->minValue = minValue;
  this->previousReading = -100;
  reset();
}

/**
 * Method to get the minimum value
 * @return The minimum value
 */
unsigned int PotentiometerRead::getMinValue() {
  return this->minValue;
}

/**
 * Method to set the maximum value of the potentiometer. And reset the previous reading.
 * @param maxValue The maximum value
 */
void PotentiometerRead::setMaxValue(unsigned int maxValue) {
  this->maxValue = maxValue;
  this->previousReading = -100;
  reset();
}

/**
 * Method to get the maximum value of the potentiometer.
 * @return The maximum value
 */
unsigned int PotentiometerRead::getMaxValue() {
  return this->maxValue;
}

/**
 * Method to set the confidence level of the potentiometer.
 * @param confidenceLevel The confidence level
 */
void PotentiometerRead::setConfidenceLevel(unsigned int confidenceLevel){
  this->confidenceLevel = confidenceLevel;
}

/**
 * Method to check for a change in the potentiometer.
 * @return The value of the potentiometer if it has changed, otherwise -1.
 */
int PotentiometerRead::checkForChange(){
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
 * Method to update the value of the potentiometer.
 * This method will check if the currentReading is different from the previousReading. 
 * If it is, it will increment the confidence level. 
 * If our confidence is greater than our confidence level, it will update our reading.
 */
void PotentiometerRead::updateValue(){
  currentReading = analogRead(pin);
  if(currentReading != previousReading)
    confidence++;
  else
    confidence = 0;

  if(confidence >= confidenceLevel){
    confidence = 0;
     previousReading = currentReading;
    if(reverseDirection)
      reading = map(currentReading, 0, 1023, maxValue, minValue);
    else
      reading = map(currentReading, 0, 1023, minValue, maxValue);
  }
}


/** Constructor for the HallEffectPotentiometerRead class.
 * This class extends the PotentiometerRead class, and adds the ability to read a potentiometer with a Hall Effect sensor.
 * @param pin The pin the potentiometer is connected to
 * @param minValue The minimum value of the potentiometer. (Default = 0)
 * @param maxValue The maximum value of the potentiometer. (Default = 1023)
 * @param confidenceLevel The confidence level of the potentiometer. (Default = 20)
 * @param directionalDeltaConfidence The confidence level of the potentiometer in a certain direction. (Default = 3)
 * @param reverseDirection Whether or not the potentiometer is reversed. (Default = false)
 */
HallEffectPotentiometerRead::HallEffectPotentiometerRead(unsigned int pin, unsigned int minValue, unsigned int maxValue, unsigned int confidenceLevel, int directionalDeltaConfidence, bool reverseDirection)
: PotentiometerRead(pin, minValue, maxValue, confidenceLevel, reverseDirection), directionalDeltaConfidence(directionalDeltaConfidence) {
  this->pin = pin;
  this->minValue = minValue;
  this->maxValue = maxValue;
  this->confidenceLevel = confidenceLevel;
  this->currentReading = 100;
  this->previousReading = -100;
  this->reverseDirection = reverseDirection;
  this->directionalDeltaConfidence = directionalDeltaConfidence;
  this->hallDirection = 0;
  this->hallDirCount = 0;
  pinMode(this->pin, INPUT);
  while(currentReading != previousReading){
    updateValue();
  }
  this->cfc = readValue();
}

/**
 * @brief to update the value of the potentiometer.
 * @details This function overrides the updateValue function in the PotentiometerRead class.
*/
void HallEffectPotentiometerRead::updateValue() {
  currentReading = analogRead(pin);
  if(currentReading != previousReading){
    confidence++;
  } else {
    confidence = 0;
  }
  if(confidence >= confidenceLevel){
    confidence = 0;
    bool isIncreasing = previousReading < currentReading;
    if (hallDirection == isIncreasing && hallDirCount >= directionalDeltaConfidence) {
      if (isIncreasing && reading != maxValue)
        reading++;
      else if (!isIncreasing && reading != minValue)
        reading--;
    }
    else if (hallDirection == isIncreasing)
        hallDirCount++;
    else{ 
      hallDirection = isIncreasing;
      hallDirCount = 0;
    }
    previousReading = currentReading;
  }
}

/**
 * @brief to set the directional delta confidence level.
 * @details This function sets the confidence level of the potentiometer in a certain direction.
 * @param directionalDeltaConfidence The confidence level of the potentiometer in a certain direction.
*/
void HallEffectPotentiometerRead::setDirectionalDeltaConfidence(int directionalDeltaConfidence) {
  this->directionalDeltaConfidence = directionalDeltaConfidence;
}

/**
 * @brief to get the directional delta confidence level.
 * @details This function gets the confidence level of the potentiometer in a certain direction.
 * @return The confidence level of the potentiometer in a certain direction.
*/
int HallEffectPotentiometerRead::getDirectionalDeltaConfidence() {
  return this->directionalDeltaConfidence;
}