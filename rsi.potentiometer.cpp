// Source File
#include "PotentiometerRead.h"
#include <stdexcept>

PotentiometerRead::PotentiometerRead(unsigned int pin, const char* name, unsigned int minVal, unsigned int maxVal, unsigned long debounceDelayVal, bool reverseDirection) {
  Pin = pin;
  Name = name;
  pMin = minVal;
  pMax = maxVal;
  debounceDelay = debounceDelayVal;
  reverseP_Direction = reverseDirection;
  pinMode(Pin, INPUT); //To support arduinos that do not auto set pinMode in the 'analogRead()' Function
}

unsigned int PotentiometerRead::readValue() {
  updateReading();
  return lastReading;
}

void PotentiometerRead::setMinValue(unsigned int minVal) {
  if (minVal > pMax) {
    throw std::invalid_argument("Object minimum value cannot be greater than its maximum value.");
  }
  pMin = minVal;
}

const unsigned int PotentiometerRead::getMinValue() {
  return pMin;
}

void PotentiometerRead::setMaxValue(unsigned int maxVal) {
  if (maxVal < pMin) {
    throw std::invalid_argument("Object maximum value cannot be less than its minimum value.");
  }
  pMax = maxVal;
}

const unsigned int PotentiometerRead::getMaxValue() {
  return pMax;
}

void PotentiometerRead::setDebounceDelay(unsigned long debounceDelayVal) {
  debounceDelay = debounceDelayVal;
}

const unsigned long PotentiometerRead::getDebounceDelay() {
  return debounceDelay;
}

void PotentiometerRead::updateReading() {
   unsigned int newReading = analogRead(Pin);

  if (newReading != lastReading) {
    lastChangeTime = millis();
  }
  if ((millis() - lastChangeTime) > debounceDelay) {
    if (reverseP_Direction) {
      lastReading = map(newReading, 0, 1023, pMax, pMin);
    } else {
      lastReading = map(newReading, 0, 1023, pMin, pMax);
    }
  }
}