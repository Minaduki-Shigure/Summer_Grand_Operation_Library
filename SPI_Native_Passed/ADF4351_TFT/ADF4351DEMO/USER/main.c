#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"
#include "spi.h"
#include "key.h"
#include "LCD12864.h"
#include <math.h>
#include "KeyBoard.h"
//extern int Enter_flag;

int main(void)
{ 
	
	uint64_t Data=0;
	float Data_show1=0;
	int Data_show2=0;
	int i=0;
//	EXTIX_Init();
	SPI1_Init();				//SPI初始化
	delay_init(168);	    	 //延时函数初始化	  
	uart_init(115200);	 	//串口初始化为9600
	reset_init();
	LCD_Init();
	Init_KeyBoard_Port();
	KeyBoard_Interrupt_Init();
	LCD_Display_Dir(1);
	LCD_DisplayOn();
	LCD_Clear(DARKBLUE);
	POINT_COLOR=WHITE;
	BACK_COLOR=DARKBLUE;
	LCD_ShowString(30,20,400,32,32,"SPI communicate TEST");
	/*for(i=0;i<3;i++){
			GPIO_ResetBits(GPIOA,GPIO_Pin_3); // flag = 0
			delay_us(50);
			GPIO_SetBits(GPIOA,GPIO_Pin_3); // flag = 1	
			delay_us(50);
		}*/
	while(1) 
	{
		if(ReadKeyBoard()!=100){
			GPIO_ResetBits(GPIOA,GPIO_Pin_3); // flag = 0
			delay_us(50);
			GPIO_SetBits(GPIOA,GPIO_Pin_3); // flag = 1	
			delay_us(50);
		}
		GPIO_ResetBits(GPIOA,GPIO_Pin_3); // flag = 0	
		Data=SPI_SendReadByte8x5(0x00000002);
		GPIO_SetBits(GPIOA,GPIO_Pin_3); // flag = 1	
		Data_show1=(double)Data;
		LCD_ShowFloat(30,100,Data_show1,3,10,32);
		Data_show2=(int)Data;
		LCD_ShowNum(30,180,Data_show2,4,32);
		
	} 
	
}
