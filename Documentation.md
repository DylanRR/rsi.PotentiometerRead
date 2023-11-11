
# PotentiometerRead Library Documentation
## Overview
The PotentiometerRead library provides an interface for reading values from a ```potentiometer``` connected to an Arduino board.
## Class Definition
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

## Public Methods

### Constructor

    PotentiometerRead(unsigned int pin, const char* name, unsigned int minVal = 0, unsigned int maxVal = 1023, unsigned long debounceDelayVal = 10, bool reverseDirection = false);

Initializes a new instance of the ```PotentiometerRead``` class. The ```pin``` parameter specifies the Arduino pin that the potentiometer is connected to. The ```name``` parameter is a string that identifies the potentiometer. The ```minVal``` and ```maxVal``` parameters define the range of values that the potentiometer can output. The ```debounceDelayVal``` parameter is used to eliminate noise in the potentiometer reading. If ```reverseDirection``` is set to ```true```, the direction of the potentiometer’s output will be reversed.

### readValue
    int readValue();
Returns the current reading from the potentiometer.

### setMinValue
    void setMinValue(unsigned int minVal);
Sets the minimum value that the potentiometer can output. Throws an ```std::invalid_argument``` exception if minVal is greater than the current maximum value.

### getMinValue
    unsigned int getMinValue();
Returns the minimum value that the potentiometer can output.
### setMaxValue
    void setMaxValue(unsigned int maxVal);
Sets the maximum value that the potentiometer can output. Throws an ```std::invalid_argument``` exception if ```maxVal``` is less than the current minimum value.
### getMaxValue
    unsigned int getMaxValue();
Returns the maximum value that the potentiometer can output.
### setDebounceDelay
    void setDebounceDelay(unsigned long debounceDelayVal);
Sets the debounce delay value. This is used to eliminate noise in the potentiometer reading.
### getDebounceDelay
    unsigned long getDebounceDelay();
Returns the current debounce delay value.

## Private Methods
### updateReading
    void updateReading();
Updates the current reading from the potentiometer. This method is called internally by the ```readValue``` method and levrages ```debounceDelay``` to filter out noise.
