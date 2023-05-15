/*
 * LED.c
 *
 *  Created on: Feb 23, 2023
 *      Author: Esraa Beshir
 */


#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../../MCAL/RCC/RCC.h"

#include "LED.h"

LED_enuErrorStatus_t Led_init(void) {
	LED_enuErrorStatus_t Loc_enuErrorStatue = LED_enuOk;
	u8 Loc_u8LedCount = sizeof(LED_AstrCfg) / sizeof(LED_AstrCfg[0]);
	u8 Loc_u8Index = 0;
	gpio_Cfg_t led;
	led.mode = GPIO_Mode_GP_PP;
	for (Loc_u8Index = 0;
			Loc_u8Index < Loc_u8LedCount && Loc_enuErrorStatue == LED_enuOk;
			Loc_u8Index++) {
		led.pin = LED_AstrCfg[Loc_u8Index].pin;
		led.port = LED_AstrCfg[Loc_u8Index].port;
		led.speed = LED_AstrCfg[Loc_u8Index].speed;
		Loc_enuErrorStatue = gpio_initPin(&led);
		if ((GPIO_enuErrorStatus_t)Loc_enuErrorStatue != GPIO_enuOk)
				{
					Loc_enuErrorStatue = LED_enuNotOk;

				}
	}

	return Loc_enuErrorStatue;
}

LED_enuErrorStatus_t Led_SetState(u8 Copy_u8Led, u8 Copy_u8State) {
	LED_enuErrorStatus_t Loc_enuErrorStatue = LED_enuOk;
	if (Copy_u8Led >= LED_Count) {
		Loc_enuErrorStatue = LED_enuInvalidLed;
	} else if (Copy_u8State != LED_State_OFF && Copy_u8State != LED_State_ON) {
		Loc_enuErrorStatue = LED_enuInvalidState;
	} else {
		Loc_enuErrorStatue = gpio_writePinValue(LED_AstrCfg[Copy_u8Led].port,
				LED_AstrCfg[Copy_u8Led].pin,
				LED_AstrCfg[Copy_u8Led].mode ^ Copy_u8State);
		if ((GPIO_enuErrorStatus_t)Loc_enuErrorStatue != GPIO_enuOk)
		{
			Loc_enuErrorStatue = LED_enuNotOk;

		}
	}
	return Loc_enuErrorStatue;
}

LED_enuErrorStatus_t Led_Toggle(u8 Copy_u8Led) {
	LED_enuErrorStatus_t Loc_enuErrorStatue = LED_enuOk;
	if (Copy_u8Led >= LED_Count) {
		Loc_enuErrorStatue = LED_enuInvalidLed;
	} else {
		u8 LedStatus;
		Loc_enuErrorStatue = gpio_getPinValue(LED_AstrCfg[Copy_u8Led].port,
				LED_AstrCfg[Copy_u8Led].pin, &LedStatus);
		if ((GPIO_enuErrorStatus_t)Loc_enuErrorStatue != GPIO_enuOk) {
			Loc_enuErrorStatue = LED_enuNotOk;

		} else {
			//LedStatus ^= 1;
			Loc_enuErrorStatue = gpio_writePinValue(
					LED_AstrCfg[Copy_u8Led].port, LED_AstrCfg[Copy_u8Led].pin,
					 LedStatus^1);
			if ((GPIO_enuErrorStatus_t)Loc_enuErrorStatue != GPIO_enuOk) {
				Loc_enuErrorStatue = LED_enuNotOk;

			}
		}
	}
	return Loc_enuErrorStatue;
}
