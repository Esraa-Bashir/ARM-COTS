/*
 * LCD.h
 *
 *  Created on: Mar 25, 2023
 *      Author: Esraa Beshir
 */

#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

#define LCD_DisplayClearCommand				0x01
#define LCD_ReturnHomeCommand				0x02

#define LCD_EntryMode_Increase			0x06
#define LCD_EntryMode_Decrease			0x04

#define LCD_FunctionSet_8Bits_1Line_5x7		0x30
#define LCD_FunctionSet_8Bits_2Line_5x7		0x38
#define LCD_FunctionSet_4Bits_1Line_5x7		0x20
#define LCD_FunctionSet_4Bits_2Line_5x7		0x28
#define LCD_FunctionSet_8Bits_1Line_5x10	0x34
#define LCD_FunctionSet_8Bits_2Line_5x10	0x3C
#define LCD_FunctionSet_4Bits_1Line_5x10	0x24
#define LCD_FunctionSet_4Bits_2Line_5x10	0x2C

#define	LCD_DisplayControl_ON_CON_CBLink		0x0F
#define	LCD_DisplayControl_ON_CON_CNotBlink		0x0E
#define	LCD_DisplayControl_ON_COFF				0x0C
#define	LCD_DisplayControl_OFF					0x08


typedef enum{
	LCD_enuOK=0,
	LCD_enuNotOK,
	LCD_enuNullPtr
	}LCD_enuErrorStatus;


typedef enum{
	LCD_Ideal=0,
	LCD_Busy,

}LCD_state_t;
void Lcd_vidInitPins(void) ;
void LCD_vidInit ();
u8 LCD_enuClearScreen(void);
u8 LCD_enuWriteString (char* Add_pchString,u8 cpy_len, u8 xpos ,u8 ypos);



#endif /* HAL_LCD_LCD_H_ */
