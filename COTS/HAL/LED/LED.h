/*
 * LED.h
 *
 *  Created on: Feb 23, 2023
 *      Author: Esraa Beshir
 */

#ifndef HAL_LED_LED_H_
#define HAL_LED_LED_H_

#include "LED_CFG.h"

#define LED_Mode_ActiveHigh		0
#define LED_Mode_ActiveLow		1

#define LED_State_ON			1
#define LED_State_OFF			0


typedef struct {

	void * port;
	u32 pin;
	u16 mode; /* active high or active low */
	u8 speed;
}LED_strCfg_t;

typedef enum {
	LED_enuOk = 0,
	LED_enuNotOk,
	LED_enuNullPtr,
	LED_enuInvalidLed,
	LED_enuInvalidState,
} LED_enuErrorStatus_t;

extern LED_strCfg_t LED_AstrCfg [LED_Count];

/***************************************************************************************/
/*  this function initialize all Leds configuration 					     		   */
/*	input : void												                       */
/*	output :Error status (LED_enuOk  ,	LED_enuNotOk)								   */
/***************************************************************************************/
LED_enuErrorStatus_t Led_init(void);


/***************************************************************************************/
/*  this function set LED state to be ON or OFF		 					     		   */
/*	input : the led to set state and the state					                       */
/*	output :Error status (LED_enuOk  ,	LED_enuNotOk , LED_enuInvalidLed,			   */
/*							LED_enuInvalidState )  									   */
/***************************************************************************************/
LED_enuErrorStatus_t Led_SetState(u8 Copy_u8Led , u8 Copy_u8State);

/***************************************************************************************/
/*  this function toggle LED				 		 					     		   */
/*	input : the led to toggle									                       */
/*	output :Error status (LED_enuOk  ,	LED_enuNotOk , LED_enuInvalidLed)			   */
/***************************************************************************************/
LED_enuErrorStatus_t Led_Toggle(u8 Copy_u8Led);
#endif /* HAL_LED_LED_H_ */
