#include <OneWire.h>
#include <DallasTemperature.h>

int moisture = 0;
const int moistureSensor1Pin = A0;//Declare a variable for the soil moisture sensor 
const int soilPower = 8;//Variable for Soil moisture Power
const int waterPumpPin = 11;
const int lightSensor = A5;
const int tempSensor = 9;
const unsigned long defaultDelayBetweenWatering = 518400;//water about once a week according to https://plantaddicts.com/watering-dianthus/#:~:text=Carnations%20typically%20need%20to%20be,rainfall%2C%20humidity%2C%20or%20dryness.
unsigned long lastWateredInMillis = 0;
OneWire oneWire(tempSensor);
DallasTemperature tempSensors(&oneWire);

void turnPumpOn(int secondsToPumpFor)
{
  digitalWrite(waterPumpPin, HIGH);
  delay(secondsToPumpFor * 1000);
  digitalWrite(waterPumpPin, LOW);
}

void turnPumpOn()
{
  digitalWrite(waterPumpPin, HIGH);
}

float getTempInCelsius()
{
  tempSensors.requestTemperatures();

  return tempSensors.getTempCByIndex(0);
}

int getMoisture()
{
    digitalWrite(soilPower, HIGH);//turn D8 "On"
    delay(200);
    moisture = analogRead(moistureSensor1Pin);//Read the SIG value form sensor #
    //val 0 = bone dry
    //val ~880+ is totally underwater
    digitalWrite(soilPower, LOW);//turn D8 "Off"
    return moisture;//send current moisture value
}

void setup() 
{
  Serial.begin(9600);   // open serial over USB
  tempSensors.begin();
  pinMode(waterPumpPin, OUTPUT);
  pinMode(soilPower, OUTPUT);//Set D8 as an OUTPUT
  digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor
  digitalWrite(waterPumpPin, LOW);
}

void loop() 
{
//This block takes sensor readings
int currentMoisture = getMoisture();
int currentTempInCelsius = getTempInCelsius();

Serial.print("Light Level = ");    
Serial.println(analogRead(lightSensor));

Serial.print("Temperature = ");    
Serial.println(currentTempInCelsius);

Serial.print("Soil Moisture = ");    
Serial.println(currentMoisture);

if (millis() - lastWateredInMillis > defaultDelayBetweenWatering && currentMoisture < 300)//Water due to time since last watering
{
  turnPumpOn(5);
  lastWateredInMillis = millis();
}
else if (millis() - lastWateredInMillis > (defaultDelayBetweenWatering/2) && currentMoisture < 600)//Water due to current moisture levels, although it must have been some time to prevent overwatering
{
  turnPumpOn(5);
  lastWateredInMillis = millis();
}
else if (millis() - lastWateredInMillis > (defaultDelayBetweenWatering/2) && currentTempInCelsius > 20)//Water due to temperature
{
  turnPumpOn(5);
  lastWateredInMillis = millis();  
}

delay(60000);//take a reading every minute
}