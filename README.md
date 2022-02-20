Atmega-Fan-Controller


 Fan controlled automatically with temperature sensor
 Fan Controller, the fan is automatically turned ON or OFF according to the temperature.
 
The temperature sensor (LM35) will continuously convert Analog temperature to digital temp_values (volt).

The LCD displays the fan state and the temperature from LM35 sensor.
 
 Conditions:
 
Temperature <  30   -->  FAN OFF

Temperature >= 30   -->  FAN speed = 25%  of Max Speed

Temperature >= 60   -->  FAN speed = 50%  of Max Speed

Temperature >= 90   -->  FAN speed = 75%  of Max Speed

Temperature >= 120  -->  FAN speed = 100% of Max Speed
		 
![image](https://user-images.githubusercontent.com/63435727/154865958-3ff5940a-9d5a-454e-b720-e942228e2d30.png)
