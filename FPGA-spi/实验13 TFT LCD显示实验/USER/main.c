#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcdx.h"
#include "spi.h"
#include "spix.h"
#include "exti.h"

//ALIENTEK 探索者STM32F407开发板 实验13
//LCD显示实验-库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

uint64_t data_f,data[20]={0};
u8 new_signal_flag;
void Display_Wave(void);


int main(void)
{ 
	double frequency=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);      //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	
	SPI1_Init();
	SPI1_SetSpeed(SPI_BaudRatePrescaler_256);		//设置为84/n时钟
	//SPIx_Init();
	EXTIX_Init();
	LED_Init();					  //初始化LED
 	LCD_Init();           //初始化LCD FSMC接口
	LCD_Display_Dir(1);		//Horizontal
	LCD_Clear(DARKBLUE);
	POINT_COLOR=LIGHTGREEN;
  //LCD_ShowCoordinateSystem(40,430,10,8,70,32,0,0,8,16);
	//Display_Color();
  while(1)
	{
		LCD_ShowxString(30,30,400,32,32,(u8*)"Explorer STM32F4",1);	
		//Display_Wave();
		if(new_signal_flag)
		{
			LCD_Fill(30,170,200,200,BLUE);
			LCD_Fill(30,280,200,460,BLUE);
			frequency = data_f;
			LCD_ShowxFloat(30,170,frequency,2,10,32,1);
			LCD_ShowxFloat(30,280,data[0],2,10,32,1);
			LCD_ShowxFloat(30,310,data[1],2,10,32,1);
			LCD_ShowxFloat(30,340,data[2],2,10,32,1);
			LCD_ShowxFloat(30,370,data[3],2,10,32,1);
			LCD_ShowxFloat(30,400,data[4],2,10,32,1);
			LCD_ShowxFloat(30,430,data[5],2,10,32,1);
			new_signal_flag = 0;
		}
	}
}

void Display_Wave(void)
{
	int i,display[20],y1,y2;
	for(i=0; i<20; i++)
	{
		display[i]=(data[i]*2/256-1)*5;								//change to voltage
	}
	for(i=0; i<20; i++)
	{
		display[i]=display[i]*(-0.22)+330;			//change to coordinate
	}
	y1=display[0];
	LCD_DrawPoint(370,y1);  //画出了第一个点
	for(i=0; i<20; i++)
	{
		y2=display[i];
		LCD_DrawLine(40+25*i,y1,40+25*(i+1),y2);
		y1 = y2;
		delay_ms(7);
	}
	LCD_DrawPoint(370,y1);  //画出了第一个点
}

