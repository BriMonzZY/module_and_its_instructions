## **bsp_xpt2046_lcd.c**



**void XPT2046_TouchEvenHandler(void)**

==检测触摸，至少10ms调用一次==





**void XPT2046_TouchDown(strType_XPT2046_Coordinate * touch)**	

==可以编辑按下后发生的事件==



## **bsp_ili9341_lcd.c**



**void ILI9341_DrawRectangle ( uint16_t usX_Start, uint16_t usY_Start, uint16_t usWidth, uint16_t usHeight, uint8_t ucFilled )**		

==画矩形==





**void ILI9341_DispString_EN_CH ( 	uint16_t usX , uint16_t usY, char * pStr )**		

==显示对应字符串==



## **palette.c**

关于按钮初始化函数和一些画板初始化，以及按键执行函数都在这里面。