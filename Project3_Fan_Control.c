/******************************************************************************************************
File Name	: Project3_Fan_Control.c
Author		: Sherif Beshr
Description : Fan Controller, the fan is automatically turned ON or OFF according to the temperature.
			  The temperature sensor (LM35) will continuously convert Analog temperature to digital temp_values (volt).
			  The LCD displays the fan state and the temperature from LM35 sensor.
 *******************************************************************************************************/

#include "std_types.h"
#include "lcd.h"
#include "adc.h"
#include "lm35_sensor.h"
#include "dc_motor.h"

int main(void)
{
	/*	Initializations of LCD, ADC, and DC motor
	 * 	The ADC will run with reference volt of 2.56V and ADC_clock = F_CPU/8 = 1MHz/8 = 125KHz
	 */
	ADC_ConfigType ADC_Config = { INTERNAL_2_56V, FCPU_8 };
	ADC_init(&ADC_Config);
	LCD_init();
	DcMotor_Init();

	/* Variable to store the temperature from LM35*/
	uint8 temp_value;

	/* Initial text to display on LCD*/
	LCD_displayStringRowColumn(0, 2, "FAN IS OFF");
	LCD_displayStringRowColumn(1, 2, "Temp =    C");

	while(1)
	{
		/* Temperature value calculated from the LM35 sensor with ADC module*/
		temp_value = LM35_getTemperature();

		LCD_displayStringRowColumn(1,8," ");			/* Set Cursor position "Temp = |...."*/

		/* If the temperature is decreases from 100 to 99 deletes the third digit*/
		if (temp_value < 100 )
		{
			LCD_intgerToString(temp_value);
			LCD_displayCharacter(' ');
		}
		else
		{
			LCD_intgerToString(temp_value);
		}

		/* Temperature <  30   -->  FAN OFF
		 * Temperature >= 30   -->  FAN speed = 25%  of Max Speed
		 * Temperature >= 60   -->  FAN speed = 50%  of Max Speed
		 * Temperature >= 90   -->  FAN speed = 75%  of Max Speed
		 * Temperature >= 120  -->  FAN speed = 100% of Max Speed
		 */
		if (temp_value >= 120)
		{
			DcMotor_Rotate(CW, 100);						/* Fan Speed = 100% */
			LCD_displayStringRowColumn(0,9,"ON 100%");		/* Set cursor position "FAN IS |..." */
		}
		else if (temp_value >= 90)
		{
			DcMotor_Rotate(CW, 75);							/* Fan Speed = 75% */
			LCD_displayStringRowColumn(0,9,"ON 75% ");		/* Set cursor position "FAN IS |..." and delete third digit */
		}
		else if (temp_value >= 60)
		{
			DcMotor_Rotate(CW, 50);							/* Fan Speed = 75% */
			LCD_displayStringRowColumn(0,9,"ON 50% ");		/* Set cursor position "FAN IS |..." and delete third digit */
		}
		else if (temp_value >= 30)
		{
			DcMotor_Rotate(CW, 25);							/* Fan Speed = 25% */
			LCD_displayStringRowColumn(0,9,"ON 25% ");		/* Set cursor position "FAN IS |..." and delete third digit */
		}
		else if (temp_value < 30)
		{
			DcMotor_Rotate(STOP, 0);						/* Fan is OFF */
			LCD_displayStringRowColumn(0,9,"OFF   ");		/* Set cursor position "FAN IS |..." and delete all digits */
		}
	}
}
