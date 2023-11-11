
# Potentiometer Library
<a href="https://github.com/DylanRR/rsi.PotentiometerRead/wiki/PotentiometerRead-Library-Documentation" target="_blank" rel="noopener noreferrer">
    <img alt="Static Badge" src="https://img.shields.io/badge/Documentation-Visit-<COLOR>">
</a>





The provided code is a C++ library designed for Arduino boards to interact with a potentiometer, a type of variable resistor often used as a sensor. The library provides an interface for reading values from a potentiometer, mapping the raw analog reading (0-1023) to a user-defined range (minimum and maximum values), and incorporating a debounce delay to prevent rapid changes in the reading due to minor fluctuations. It also allows for the direction of the reading to be reversed if needed.



## Usage/Examples

This library can be used in a variety of projects. For instance, it can be used to read sensor values in projects where potentiometer readings are required, such as in light dimmers or volume controls in audio devices. It can also be used to get user input in interactive projects, like controlling the movement of a robot or changing the blink rate of an LED. The library’s ability to map the potentiometer reading to a specific range of values and its feature to reduce noise through debounce delay make it adaptable to a wide range of applications. Please note that this is a general-purpose library and its use is not limited to these examples. It can be adapted to suit the needs of various projects involving potentiometers.

    PotentiometerRead pot(1, "TestPot", 0, 1023, 10, false);
    void loop(){
        int output;
        output = pot.readValue();
        Serial.Print (output)
        pot.setMinVal(100)
        pot.setMaxVal(500)
    }


## Authors

- [@DylanRR](https://github.com/DylanRR)


