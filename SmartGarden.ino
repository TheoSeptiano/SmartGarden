#include <OneWire.h>
#include <DallasTemperature.h>

int moisture = 0;
const int moistureSensorPin = A0; 
const int soilPower = 8;//pin that powers the moisture sensor
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

void turnPumpOn()//if no duration is supplied, waters until turnPumpOff() is called
{
  digitalWrite(waterPumpPin, HIGH);
}

void turnPumpOff()//if no duration is supplied, waters until turnPumpOff() is called
{
  digitalWrite(waterPumpPin, LOW);
}

float getTempInCelsius()
{
  tempSensors.requestTemperatures();

  return tempSensors.getTempCByIndex(0);
}

int getMoisture()
{
    digitalWrite(soilPower, HIGH);//turn moisture sensor on
    delay(200);
    moisture = analogRead(moistureSensorPin);
    //val 0 = bone dry
    //val ~880+ is totally underwater
    digitalWrite(soilPower, LOW);//turn moisture sensor off
    return moisture;
}

void setup() 
{
  Serial.begin(9600);
  tempSensors.begin();
  pinMode(waterPumpPin, OUTPUT);
  pinMode(soilPower, OUTPUT);
  digitalWrite(soilPower, LOW);
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

if (millis() - lastWateredInMillis > (defaultDelayBetweenWatering*1000) && currentMoisture < 300)//Water due to time since last watering
{
  turnPumpOn(5);
  lastWateredInMillis = millis();
}
else if (millis() - lastWateredInMillis > ((defaultDelayBetweenWatering*1000)/2) && currentMoisture < 600)//Water due to current moisture levels, although it must have been some time to prevent overwatering
{
  turnPumpOn(5);
  lastWateredInMillis = millis();
}
else if (millis() - lastWateredInMillis > ((defaultDelayBetweenWatering*1000)/2) && currentTempInCelsius > 20)//Water due to temperature
{
  turnPumpOn(5);
  lastWateredInMillis = millis();  
}

delay(60000);//take a reading every minute
}