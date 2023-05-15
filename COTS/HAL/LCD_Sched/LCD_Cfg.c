/*
 * LCD_Cfg.c
 *
 *  Created on: Mar 25, 2023
 *      Author: Esraa Beshir
 */

#include "../../MCAL/GPIO/GPIO.h"
 #include "LCD.h"
 #include "LCD_Cfg.h"

Lcd_strCfg Lcd_strPinsCfg[11]={
		[LCD_u8PIN_RS]={.LcdPort = GPIO_PORT_A, .LcdPin =GPIO_PIN_0 },
		[LCD_u8PIN_RW]={.LcdPort = GPIO_PORT_A, .LcdPin =GPIO_PIN_1 },
		[LCD_u8PIN_EN]={.LcdPort = GPIO_PORT_A, .LcdPin =GPIO_PIN_2 },
		[LCD_u8PIN_D0]={.LcdPort = GPIO_PORT_A, .LcdPin =GPIO_PIN_3 },
		[LCD_u8PIN_D1]={.LcdPort = GPIO_PORT_A, .LcdPin =GPIO_PIN_4 },
		[LCD_u8PIN_D2]={.LcdPort = GPIO_PORT_A, .LcdPin =GPIO_PIN_5 },
		[LCD_u8PIN_D3]={.LcdPort = GPIO_PORT_A, .LcdPin =GPIO_PIN_6 },
		[LCD_u8PIN_D4]={.LcdPort = GPIO_PORT_A, .LcdPin =GPIO_PIN_7 },
		[LCD_u8PIN_D5]={.LcdPort = GPIO_PORT_A, .LcdPin =GPIO_PIN_8 },
		[LCD_u8PIN_D6]={.LcdPort = GPIO_PORT_A, .LcdPin =GPIO_PIN_9 },
		[LCD_u8PIN_D7]={.LcdPort = GPIO_PORT_A, .LcdPin =GPIO_PIN_10 },
};
