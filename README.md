# Temperature-Monitor
This is a lab for METE 2030U (Electronics Applications in Mechatronics). I created a Temperature Monitoring System with the Atmega 328P (Arduino) microcontroller coded in C++.
At it's core, a thermistor measured the temperature and relayed that signal as a voltage to the Arduino. That voltage signal (0-5V) was then converted from analog to digital (10-bit resolution, from 0-1023) using the ADC (Analog to Digital Converter) feature provided by the analogRead() function.
