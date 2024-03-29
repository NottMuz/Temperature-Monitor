# Temperature-Monitor
This is the final lab project for METE 2030U (Electronics Applications in Mechatronics). I created a Temperature Monitoring System with the ATmega 328 (Arduino Mega 2560) microcontroller which was coded in C++.

# The In-Depth
 - At its core, a thermistor measures the temperature and relays that signal as a voltage to the Arduino. That voltage signal (0-5V) is converted from analog to digital (at 10-bit resolution, from 0-1023) using the ADC (Analog to Digital Converter) feature provided by the analogRead() function.

- However, in order to use the Steinhart-Hart Thermistor equation to find the temperature in Kelvin the resistance of the thermistor is required. This means that the automatic ADC of the Arduino is actually a hinderance, as the analog voltage value is needed to compute the thermistor resistance. So the signal needs to be reversed back into analog.

- In order to do that, we need to understand how the Arduino actually converts the analog value to a digital 10 bit signal. We can theoretically assume it accomplishes this by using voltage divide to get the voltage across the thermistor (as an analog value) as it is series with a 10 kOhm resistor (chosen to match the nominal value for the thermistor at room temperature). Dividing the given analog value by the Analog Reference value for the Ardunio provides a ra
