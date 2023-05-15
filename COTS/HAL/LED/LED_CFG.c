/*
 * LED_CFG.c
 *
 *  Created on: Feb 23, 2023
 *      Author: Esraa Beshir
 */
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../../MCAL/RCC/RCC.h"

#include "LED.h"
#include  "LED_CFG.h"

LED_strCfg_t LED_AstrCfg[LED_Count] = {
/* ex : [LED_Warning] = 		 */
/* { .port = GPIO_PORT_A ,		 */
/* .pin = GPIO_PIN_0,			 */
/* .speed = GPIO_Speed_Low,		 */
/* .mode = LED_Mode_ActiveHigh}, */

[LED_Alarm] =
{ .port = GPIO_PORT_A, .pin = GPIO_PIN_0, .speed = GPIO_Speed_Low, .mode =
LED_Mode_ActiveHigh},

[LED_Stop] =
{ .port = GPIO_PORT_A, .pin = GPIO_PIN_1, .speed = GPIO_Speed_Low, .mode =
LED_Mode_ActiveHigh },

[LED_Inc] =
{ .port = GPIO_PORT_A, .pin = GPIO_PIN_2, .speed = GPIO_Speed_Low, .mode =
LED_Mode_ActiveHigh },

[LED_Dec] =
{ .port = GPIO_PORT_A, .pin = GPIO_PIN_3, .speed = GPIO_Speed_Low, .mode =
LED_Mode_ActiveHigh }, };
