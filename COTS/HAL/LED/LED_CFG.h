/*
 * LED_CFG.h
 *
 *  Created on: Feb 23, 2023
 *      Author: Esraa Beshir
 */

#ifndef HAL_LED_LED_CFG_H_
#define HAL_LED_LED_CFG_H_



typedef enum {
	/* add the name of the leds make sure not to delete LED_Count and make it the last element in the enum */
	/* ex: LED_Warning ,  */
	LED_Alarm = 0, LED_Stop, LED_Inc, LED_Dec, LED_Count
}LED_enuLedNames_t;



#endif /* HAL_LED_LED_CFG_H_ */
