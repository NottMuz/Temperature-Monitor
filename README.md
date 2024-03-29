# Temperature-Monitor
This is the final lab project for METE 2030U (Electronics Applications in Mechatronics). I created a Temperature Monitoring System with the ATmega 328 (Arduino Mega 2560) microcontroller which was coded in C++. After completing the lab I decided to take it a step further and 3-D print a chassis and add a DHT 11 humidity sensor and a Real-Time-Clock Module to create an informative device I can just have running on my desk. That is not the focus of this repo though, so the rest of the read.me will be in relation to the operation of the temperature monitor, as there are many real-world uses for its integration in circuitry and other systems that become volatile when running outside of the optimal operating temperatures.

# The In-Depth
 - At its core, a thermistor measures the temperature and relays that signal as a voltage to the Arduino. That voltage signal (0-5V) is converted from analog to digital (at 10-bit resolution, from 0-1023) using the ADC (Analog to Digital Converter) feature provided by the analogRead() function.

- However, in order to use the Steinhart-Hart Thermistor equation to find the temperature in Kelvin the resistance of the thermistor is required. This means that the automatic ADC of the Arduino is actually a hinderance, as the analog voltage value is needed to compute the thermistor resistance. So the signal needs to be reversed back into analog.

- In order to do that, we need to understand how the Arduino actually converts the analog value to a digital 10 bit signal. We can theoretically assume it accomplishes this by using voltage divide to get the voltage across the thermistor (as an analog value) as it is series with a 10 kOhm pull-down resistor (chosen to match the nominal value for the thermistor at room temperature). Dividing the obtained analog voltage value by the Analog-Reference-Value (for the Arduino the standard is 5V, however you need to set it at whatever the maximum operating voltage is for the device) provides a ratio of the actual value to its maximum possible value.

   - **` maximumThermistorVoltage = 5; `**  
   - **` currentThermisterVoltage = analogRead(V_thermistor) = [R/(R+10,000)]*Vcc; `**
   - **` analogVoltageRatio = currentThermistorVoltage / maximumThermistorVoltage; `**

- Sound/look familiar yet? Let's say that the voltage range for the thermistor is from 0-5V, all that happens when the Arduino converts that analog value to a relative digital value is that it maps that ratio (0:5) to (0:1023). To illustrate this, I have provided a 
