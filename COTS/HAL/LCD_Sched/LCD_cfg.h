/*
 * LCD_cfg.h
 *
 *  Created on: Mar 25, 2023
 *      Author: Esraa Beshir
 */

#ifndef HAL_LCD_LCD_CFG_H_
#define HAL_LCD_LCD_CFG_H_

/*
choose the function set between
 LCD_FunctionSet_8Bits_1Line_5x7
 LCD_FunctionSet_8Bits_2Line_5x7
 LCD_FunctionSet_8Bits_1Line_5x10
 LCD_FunctionSet_8Bits_2Line_5x10

*/
#define LCD_FunctionSet	LCD_FunctionSet_8Bits_2Line_5x7

/*
   choose the display control from
	LCD_DisplayControl_ON_CON_CBLink
	LCD_DisplayControl_ON_CON_CNotBlink
	LCD_DisplayControl_ON_COFF
	LCD_DisplayControl_OFF

*/

#define  LCD_DisplayControl	LCD_DisplayControl_ON_CON_CBLink

/*
	choose the entry mode from
	 LCD_EntryMode_Increase
	 LCD_EntryMode_Decrease
*/

#define	LCD_EntryMode	LCD_EntryMode_Increase

typedef enum{
	LCD_u8PIN_RS=0,
	LCD_u8PIN_RW,
	LCD_u8PIN_EN,
	LCD_u8PIN_D0,
	LCD_u8PIN_D1,
	LCD_u8PIN_D2,
	LCD_u8PIN_D3,
	LCD_u8PIN_D4,
	LCD_u8PIN_D5,
	LCD_u8PIN_D6,
	LCD_u8PIN_D7
}Lcd_pins;

typedef struct {
	void * LcdPort;
	u16 LcdPin;
}Lcd_strCfg;

extern Lcd_strCfg Lcd_strPinsCfg[11];


#endif /* HAL_LCD_LCD_CFG_H_ */
