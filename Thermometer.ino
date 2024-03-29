//Name: Muzzammil Rehman
//Date: 27/03/2024

//Liquid Crystal is the library for the display
#include <LiquidCrystal.h>
//For I2C communication, interfaces with devices that use it
#include <Wire.h>
//DHT library for the DHT 11 humidity sensor
#include <DHT.h>
//Real-Time-Clock Module for the 
#include <RTClib.h>

// Define DHT sensor pin and type
#define DHTPIN 2
#define DHTTYPE DHT11
//initialize a DHT object to use the library
DHT dht(DHTPIN, DHTTYPE);

//initialize DS3231 RTC
RTC_DS3231 rtc;

//pin which the temperature will be read from
int tempPin = 0;

//digital I/O pins that are used for the LED indicators
int blueLed = 3;
int redLed = 2;

//initialize the LCD object with the provided parameters
//for the pins
//                BS E  D4 D5  D6  D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

//runs once for initialization purposes
void setup()
{
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize DHT sensor
  dht.begin();

  // Initialize LCD
  lcd.begin(16, 2);  // 16 columns, 2 rows
  lcd.setCursor(0, 1);  // Set cursor to second row, first column
  lcd.print("Humidity: ");  // Print initial text

  // Initialize DS3231 RTC
  if (!rtc.begin()) {  // Check if RTC module is not found
    lcd.setCursor(0, 1);  // Set cursor to second row, first column
    lcd.print("RTC not found!");  // Print error message
    while (1);  // Stop program
 
  // Set the time and date to the RTC if not set
  if (!rtc.isrunning()) {  // Check if RTC is not running
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // Set time and date from compile time
    
  //set led identifier pins as output
  pinMode(blueLed,OUTPUT);
  pinMode(redLed,OUTPUT);
}

//looping function
void loop()
{
   // Read humidity from DHT sensor
  float humidity = dht.readHumidity();

  // Read date and time from RTC
  DateTime now = rtc.now();

  // Display humidity on LCD
  lcd.setCursor(10, 0);  // Set cursor to first row, 10th column
  lcd.print(humidity);  // Print humidity value
  lcd.print(" %");  // Print unit

  // Display date and time on LCD
  lcd.setCursor(0, 1);  // Set cursor to second row, first column
  lcd.print(now.year(), DEC);  // Print year
  lcd.print("/");  // Print separator
  lcd.print(now.month(), DEC);  // Print month
  lcd.print("/");  // Print separator
  lcd.print(now.day(), DEC);  // Print day
  lcd.print(" ");  // Print separator
  lcd.print(now.hour(), DEC);  // Print hour
  lcd.print(":");  // Print separator
  if (now.minute() < 10) {  // Add leading zero if minute is less than 10
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);  // Print minute
  lcd.print(":");  // Print separator
  if (now.second() < 10) {  // Add leading zero if second is less than 10
    lcd.print("0");
  }
  lcd.print(now.second(), DEC);  // Print second

  //store analog signal from specified pin (A0) [as an integer 10-bit value, from 0-1023]
  int tempReading = analogRead(tempPin);
  
  //Convert Analog Reading to Kelvin
  double thermistorResistance = log(10000.0 * ((1024.0 / tempReading - 1)));

  //Convert Thermistor Resistance to temperature in Kelvin;
  double tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 *thermistorResistance* thermistorResistance )) * thermistorResistance ); 
  
  // Convert Kelvin to Celcius
  float tempC = tempK - 273.15;            

  //BLUE LED CODE
  if (tempC < 26)
    {
      digitalWrite(blueLed, HIGH);
      digitalWrite(redLed, LOW);
    }
    
   //RED LED CODE
   if(tempC > 28)
   {
    digitalWrite(redLed, HIGH);
    delay(1000);
    digitalWrite(redLed, LOW);
   }

   //In between code
 else if (tempC >= 26 && tempC <=28)
    {
      digitalWrite(blueLed, LOW);
    }


    
  float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  
  /*  replaced
   *   //converts the analog signal from 10 bits to readable voltage (5V supplied)
    float tempVolts = tempReading * 5.0 / 1024.0;
    
    float tempC = (tempVolts - 0.5) * 10.0;
    float tempF = tempC * 9.0 / 5.0 + 32.0;
  */
  
  // Display Temperature in C
  
  // Identify position of Text
  lcd.setCursor(0, 0);
  //         01234567891111
  //                   0123
  lcd.print("Temp         C  ");
  
  // Display Temperature in F
  //lcd.print("Temp         F  ");

  
  lcd.setCursor(6, 0);
  // Display Temperature in C
  lcd.print(tempC);

  
  // Display Temperature in F
  //lcd.print(tempF);
  delay(100);
}
