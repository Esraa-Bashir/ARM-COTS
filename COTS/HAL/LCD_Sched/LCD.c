/*
 * LCD.c
 *
 *  Created on: Mar 25, 2023
 *      Author: Esraa Beshir
 */

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../../MCAL/RCC/RCC.h"
#include "LCD.h"
#include "LCD_Cfg.h"

typedef struct {
	const u8 * string;
	u8 str_len;
	u8 xpos;
	u8 ypos;
	u8 request_type;

} LCD_requestHandler;

typedef enum {
	LCD_NoTask, LCD_WriteStringRequest, LCD_ClearScreenRequest,
} LCD_requestsTypes;

typedef enum {
	LCD_FunctionSet_Stage = 0,
	LCD_DisplayControl_Stage,
	LCD_DisplayClearCommand_Stage,
	LCD_EntryMode_Stage,
	LCD_Finished_Stage,
} LCD_initSequence;

typedef enum {
	setposition_stage = 0, writeCharacter_stage, finishied_stage,
} writeString_sequence;

static u8 LCD_enuSendData(u8 Copy_u8Data);
static u8 LCD_enuSendCommand(u8 Copy_u8Command);
static u8 LCD_enuGotoXY_seq(void);
 void Lcd_vidInitPins(void) ;
static u8 LCD_intiallized_flag = 0;
static u8 LCD_Pinsintiallized_flag = 0;
static u8 LCD_state_flag = LCD_Ideal;
static LCD_requestHandler request;

 void Lcd_vidInitPins(void) {
	gpio_Cfg_t Gpio_CfgInit;
	u8 iterator = 0;
	switch ((u32) (Lcd_strPinsCfg[iterator].LcdPort)) {
		case (u32) GPIO_PORT_A:
			RCC_enuEnablePeripheral(RCC_AHB1, RCC_AHB1_GPIOA);
			break;
		case (u32) GPIO_PORT_B:
			RCC_enuEnablePeripheral(RCC_AHB1, RCC_AHB1_GPIOB);
			break;
		case (u32) GPIO_PORT_C:
			RCC_enuEnablePeripheral(RCC_AHB1, RCC_AHB1_GPIOC);
			break;
		case (u32) GPIO_PORT_D:
			RCC_enuEnablePeripheral(RCC_AHB1, RCC_AHB1_GPIOD);
			break;
		case (u32) GPIO_PORT_E:
			RCC_enuEnablePeripheral(RCC_AHB1, RCC_AHB1_GPIOE);
			break;
		case (u32) GPIO_PORT_H:
			RCC_enuEnablePeripheral(RCC_AHB1, RCC_AHB1_GPIOH);
			break;
		}
	Gpio_CfgInit.mode = GPIO_Mode_GP_PP;
	Gpio_CfgInit.speed = GPIO_Speed_High;
	for (iterator = 0; iterator < 11; iterator++) {
		Gpio_CfgInit.port = Lcd_strPinsCfg[iterator].LcdPort;
		Gpio_CfgInit.pin = Lcd_strPinsCfg[iterator].LcdPin;
		gpio_initPin(&Gpio_CfgInit);
	}
	trace_printf("pin intiallized \n");
LCD_Pinsintiallized_flag=1;
}

static u8 LCD_enuSendCommand(u8 Command) {
	static u8 stage = 0;
	u8 finished_flag = 0;
	switch (stage) {
	case 0:
		gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_RS].LcdPort,
				Lcd_strPinsCfg[LCD_u8PIN_RS].LcdPin, GPIO_Value_Low);
		gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_RW].LcdPort,
				Lcd_strPinsCfg[LCD_u8PIN_RW].LcdPin, GPIO_Value_Low);
		gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_EN].LcdPort,
				Lcd_strPinsCfg[LCD_u8PIN_EN].LcdPin, GPIO_Value_High);
		trace_printf("EN pin high\n");
		gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_D0].LcdPort,
				Lcd_strPinsCfg[LCD_u8PIN_D0].LcdPin, Command & 0x01);
		gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_D1].LcdPort,
				Lcd_strPinsCfg[LCD_u8PIN_D1].LcdPin, (Command>>1) & 0x01);
		gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_D2].LcdPort,
				Lcd_strPinsCfg[LCD_u8PIN_D2].LcdPin, (Command>>2) & 0x01);
		gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_D3].LcdPort,
				Lcd_strPinsCfg[LCD_u8PIN_D3].LcdPin, (Command>>3) & 0x01);
		gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_D4].LcdPort,
				Lcd_strPinsCfg[LCD_u8PIN_D4].LcdPin, (Command>>4) & 0x01);
		gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_D5].LcdPort,
				Lcd_strPinsCfg[LCD_u8PIN_D5].LcdPin, (Command>>5) & 0x01);
		gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_D6].LcdPort,
				Lcd_strPinsCfg[LCD_u8PIN_D6].LcdPin, (Command>>6) & 0x01);
		gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_D7].LcdPort,
				Lcd_strPinsCfg[LCD_u8PIN_D7].LcdPin, (Command>>7) & 0x01);
		stage++;
		break;
	case 1:
		gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_EN].LcdPort,
				Lcd_strPinsCfg[LCD_u8PIN_EN].LcdPin, GPIO_Value_Low);
		trace_printf("EN pin low \n");
		stage++;
		break;
	case 2:
		stage = 0;
		finished_flag = 1;
		break;
	}
	return finished_flag;
}

static u8 LCD_enuSendData(u8 Command) {
	static u8 stage = 0;
	u8 finished_flag = 0;
	switch (stage) {
	case 0:
		gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_RS].LcdPort,
				Lcd_strPinsCfg[LCD_u8PIN_RS].LcdPin, GPIO_Value_High);
		gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_RW].LcdPort,
				Lcd_strPinsCfg[LCD_u8PIN_RW].LcdPin, GPIO_Value_Low);
		gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_EN].LcdPort,
				Lcd_strPinsCfg[LCD_u8PIN_EN].LcdPin, GPIO_Value_High);
		trace_printf("En pin high data <3 \n");
		gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_D0].LcdPort,
						Lcd_strPinsCfg[LCD_u8PIN_D0].LcdPin, Command & 0x01);
				gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_D1].LcdPort,
						Lcd_strPinsCfg[LCD_u8PIN_D1].LcdPin, (Command>>1) & 0x01);
				gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_D2].LcdPort,
						Lcd_strPinsCfg[LCD_u8PIN_D2].LcdPin, (Command>>2) & 0x01);
				gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_D3].LcdPort,
						Lcd_strPinsCfg[LCD_u8PIN_D3].LcdPin, (Command>>3) & 0x01);
				gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_D4].LcdPort,
						Lcd_strPinsCfg[LCD_u8PIN_D4].LcdPin, (Command>>4) & 0x01);
				gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_D5].LcdPort,
						Lcd_strPinsCfg[LCD_u8PIN_D5].LcdPin, (Command>>5) & 0x01);
				gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_D6].LcdPort,
						Lcd_strPinsCfg[LCD_u8PIN_D6].LcdPin, (Command>>6) & 0x01);
				gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_D7].LcdPort,
						Lcd_strPinsCfg[LCD_u8PIN_D7].LcdPin, (Command>>7) & 0x01);
		stage++;
		break;
	case 1:
		gpio_writePinValue(Lcd_strPinsCfg[LCD_u8PIN_EN].LcdPort,
				Lcd_strPinsCfg[LCD_u8PIN_EN].LcdPin, GPIO_Value_Low);
		trace_printf("EN pin low command \n");
		stage++;
		break;
	case 2:
		stage = 0;
		finished_flag = 1;
		break;

	}
	return finished_flag;
}

void  LCD_vidInit  (){
	 static u8 stage = LCD_FunctionSet_Stage,count=0;
	 u8 flag=0;
	 switch(stage){
		 case LCD_FunctionSet_Stage:
			 if (count == 0)
			 {
				 Lcd_vidInitPins() ;
			 }
		 count ++;
		 if (count>=50){
			 trace_printf("start function set \n");
		 flag = LCD_enuSendCommand(LCD_FunctionSet);
		 if (flag==1)
		 stage++;
		 }
		 break;
		 case LCD_DisplayControl_Stage:
			 trace_printf("start display control\n");
		 flag = LCD_enuSendCommand(LCD_DisplayControl);
		 if (flag==1)
		 stage++;
		 break;
		 case LCD_DisplayClearCommand_Stage:
			 trace_printf("display clear command\n");
		 flag= LCD_enuSendCommand(LCD_DisplayClearCommand);
		 if (flag==1)
		 stage++;
		 break;
		 case LCD_EntryMode_Stage:
			 trace_printf("entry mode  \n");
		 flag = LCD_enuSendCommand(LCD_EntryMode);
		 if (flag==1)
		 stage++;
		 break;
		 case LCD_Finished_Stage:
			 trace_printf("init finished \n");
		 LCD_intiallized_flag=1;
		 stage=0;
		 break;

	 }

 }

 u8 LCD_enuWriteString (char* Add_pchString,u8 cpy_len, u8 xpos ,u8 ypos){
	 u8 loc_state=LCD_Busy;
	 if (LCD_state_flag == LCD_Ideal){
		 trace_printf("inside writing string func \n");
		 loc_state = LCD_Ideal;
		 LCD_state_flag = LCD_Busy;
		 request.request_type= LCD_WriteStringRequest;
		 request.string= Add_pchString;
		 request.str_len =cpy_len;
		 request.xpos = xpos;
		 request.ypos= ypos;
	 }
	 return loc_state;
 }

  u8 LCD_enuClearScreen(void){
	  u8 loc_state=LCD_Busy;
	  if (LCD_state_flag == LCD_Ideal){
		  trace_printf("inside clear screen func \n");
		  loc_state = LCD_Ideal;
		  LCD_state_flag = LCD_Busy;
		  request.request_type= LCD_ClearScreenRequest;
	  }
	  return loc_state;
  }

 static u8 LCD_enuWriteString_seq (void){

	 static u8 stage = setposition_stage ;
	 static u8 current_char=0;
	 u8 flag,finished_flag=0;
	 switch(stage){
		 case setposition_stage:
			 trace_printf("set position \n");
		 flag = LCD_enuGotoXY_seq();
		 if (flag==1){
			 stage ++;
		 }
		 break;
		 case writeCharacter_stage:
			 trace_printf("write character \n");
		 flag = LCD_enuSendData (request.string[current_char]);
		 if (flag==1)
		 {
			 current_char ++;
		 }
		 if (current_char == request.str_len&& flag==1)
		 {
			 current_char =0;
			 finished_flag =1;
			 stage = setposition_stage;
		 }
		 break;
		 case finishied_stage:

		 break;
	 }

	 return finished_flag;
 }




 static u8 LCD_enuClearScreen_seq(void){
	 u8 finished_flag=0;
	 finished_flag = LCD_enuSendCommand(LCD_DisplayClearCommand);
	 return finished_flag;
 }


 static u8 LCD_enuGotoXY_seq(void){
	 u8 finished_flag=0;
	 u8 Loc_u8Command = (request.xpos * (0x40) + request.ypos )+128;
	 finished_flag = LCD_enuSendCommand(Loc_u8Command );
	 return finished_flag;
 }



 /* performed each 2 msec */
 void LCD_Task(void){
	 if (LCD_intiallized_flag == 0)
	 {
		 LCD_vidInit  ();
	 }
	 else {
		 trace_printf("lcd intiallized done\n");

		 if (LCD_state_flag==LCD_Busy){
			 trace_printf("lcd intiallized done\n");
			 u8 finishedFlag=0;
			 if (request.request_type== LCD_WriteStringRequest)
			 {
				 finishedFlag =LCD_enuWriteString_seq();
			 }
			 else if (request.request_type== LCD_ClearScreenRequest){
				 finishedFlag =LCD_enuClearScreen_seq();

			 }
			 if (finishedFlag==1)
			 {
				 LCD_state_flag=LCD_Ideal;

			 }
		 }
	 }

 }
