#include <ArduinoUnit.h>
#include "PotentiometerRead.h"

// Mock analogRead function
int analogRead(int pin) {
  // Return a predefined value based on the pin number
  switch (pin) {
    case 1: return 500;
    case 2: return 1023;
    case 3: return 0;
    default: return -1;
  }
}

test(potentiometer_read) {
  PotentiometerRead pot(1, "TestPot", 0, 1023, 10, false);

  // Test initial values
  assertEqual(pot.getMinValue(), 0);
  assertEqual(pot.getMaxValue(), 1023);
  assertEqual(pot.getDebounceDelay(), 10);

  // Test setMinValue and getMinValue
  pot.setMinValue(100);
  assertEqual(pot.getMinValue(), 100);

  // Test setMaxValue and getMaxValue
  pot.setMaxValue(900);
  assertEqual(pot.getMaxValue(), 900);

  // Test setDebounceDelay and getDebounceDelay
  pot.setDebounceDelay(20);
  assertEqual(pot.getDebounceDelay(), 20);

  // Test exceptions
  try {
    pot.setMinValue(1000);
    fail("Expected exception when setting min value greater than max value");
  } catch (std::invalid_argument& e) {
    assertEqual(e.what(), "Object minimum value cannot be greater than its maximum value.");
  }

  try {
    pot.setMaxValue(50);
    fail("Expected exception when setting max value less than min value");
  } catch (std::invalid_argument& e) {
    assertEqual(e.what(), "Object maximum value cannot be less than its minimum value.");
  }

  // Test readValue with mock analogRead
  assertEqual(pot.readValue(), 500);

  PotentiometerRead pot2(2, "TestPot", 0, 1023, 10, false);
  assertEqual(pot2.readValue(), 1023);

  PotentiometerRead pot3(3, "TestPot", 0, 1023, 10, false);
  assertEqual(pot3.readValue(), 0);
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {} // Waits for a serial connection (for Leonardo/Micro/Zero)
}

void loop() {
  Test::run();
}
