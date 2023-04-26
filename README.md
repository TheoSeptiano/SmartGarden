# Smart Garden

This project waters a plant without the need for intervention (aside from filling a tank for the water pump to draw from).

The system takes into account: Temperature, Soil Moisture Levels, Time, and also outputs the current light level; although this does not factor into whether the plant is watered as it can be easily triggered by accident such as the shadow of someone admiring the plant blocking light from reaching the sensor.

I tested the project using Carnations, and it worked perfectly, but if you are caring for other types of plants you should adjust the values shown below:
* "defaultDelayBetweenWatering", this is the time in seconds between watering the plant in ideal conditions. For example, if your plant needs watering every other day, the value to put as "defaultDelayBetweenWatering" would be 172800.
* "turnPumpOn(5)", this is the number of seconds the water pump should stay on for in seconds after it has been triggered. If your plant requires more water or the layout of your water pipe makes the time taken to reach the plant longer then the value in the brackets should be increased.
* "currentTempInCelsius < 20", the "20" here denotes what I have classed as a hot day, but if your plant thrives in hotter temperatures the 20 should be increased to what would be considered a hot day for your plant.
* "currentMoisture < 300", This is the condition that triggers the water pump when your plant is too dry, if your plant requires less dry soil, the 300 should be increased.

A diagram of how to wire up your Smart Garden is shown below (with the dc motor representing the water pump):

![SmartGarden](https://user-images.githubusercontent.com/61507843/234591575-85e82a3d-c9ae-4e11-a28c-c2b4dcb2c8aa.png)

Note: The wires leading nowhere on row C should be plugged into your Light Intensity Sensor. The software I used to create the diagram did not have them available so I left a space there.

Link to video of the working solution: https://www.youtube.com/watch?v=AY0_Behodl0
