//#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
//#include "key.h"
//#include "spix.h"
//#include "exti.h"
//#include "dac.h"
#include "adc.h"
#include "spi.h"

#include <math.h>

//uint64_t SPI_NULL=0x0000000000000000;

//ALIENTEK Mini STM32开发板范例代码15
//ADC实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

/*
//fix include errors
#define SPI_PORT 	GPIOE
#define SPI_FLAG_PORT GPIOC
#define SPI_CS   	GPIO_Pin_0
#define SPI_SCLK 	GPIO_Pin_2
#define SPI_MISO 	GPIO_Pin_4
#define SPI_MOSI 	GPIO_Pin_6
#define SPI_FLAG 	GPIO_Pin_14
#define RCC_SPI  	RCC_AHB1Periph_GPIOE
#define RCC_SPI_FLAG		RCC_AHB1Periph_GPIOC

void SPIx_Init(void);
uint64_t SPIx_SendReadByte36(uint64_t byte);
uint64_t SPIx_SendReadByte16(uint64_t byte);
*/	
	
//#define SPI_FLAG_PORT GPIOC	
//#define SPI_FLAG 	GPIO_Pin_14
//#define RCC_SPI_FLAG		RCC_AHB1Periph_GPIOC
	
#define XaxisHeight 12
#define YaxisHeight XaxisHeight
	
	
 int main(void)
 { 
 	//u8 t=0;	 
	//u16 dacval=0;
	//u8 key;
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	//u8 Data_F;
	//double dutyRatio,timeInterval;
	//double dutyRatio_L,dutyRatio_N;
	//double timeInterval_L,timeInterval_N;
	//uint64_t data1=1,data2=2,data3=3,data4=4,data5=5,data6=6;//data1,data2为频率参数 data3,data4为占空比参数
	//uint64_t Data_R,Data_L;

	int i=0;
	int adcx=0; 
	int adcxx=0;
	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	delay_init(168);	    	 //延时函数初始化	  
	uart_init(115200);	 	//串口初始化为9600
	reset_init();
	//SPIx_Init();
	//SPI1_Init();
	//SPI1_SetSpeed(SPI_BaudRatePrescaler_2);
	//LED_Init();		  		//初始化与LED连接的硬件接口
 	LCD_Init();			   	//初始化LCD 		
	LCD_Display_Dir(1);
	LCD_DisplayOn();
	Adc_Init();
	//KEY_Init();				//按键初始化		 	
 	//Adc_Init();		  		//ADC初始化
	//Dac1_Init();		 	//DAC通道1初始化	
	
	//GPIO_InitTypeDef SPI_GPIO_InitStructure;
	//RCC_AHB1PeriphClockCmd(RCC_SPI_FLAG, ENABLE);
	//SPI_GPIO_InitStructure.GPIO_Pin = SPI_FLAG;//CS,SCLK,MISO
  //SPI_GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	//SPI_GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	//SPI_GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	//SPI_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
  //GPIO_Init(SPI_FLAG_PORT, &SPI_GPIO_InitStructure);	
	
	LCD_Clear(WHITE);
	LCD_Clear(BLUE);
	LCD_Clear(WHITE);
	POINT_COLOR=DARKBLUE;
	LCD_ShowString(30,20,420,24,24,(u8*)"Nanjing University");	
	LCD_ShowString(30,50,420,24,24,"   EE Group 4 ");	
	LCD_ShowString(30,80,420,24,24,"Minaduki Shigure");
	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(30,110,420,24,24,"LCD&ADC Speed Test");	
	//LCD_ShowString(60,130,200,16,16,"WK_UP:+  KEY0:-");	
	//显示提示信息											      
	POINT_COLOR=BLUE;//设置字体为蓝色
	//LCD_ShowString(30,140,500,24,24,"Frequency:");	      
	//LCD_ShowString(30,180,500,24,24,"Duty Ratio:");	      
	//LCD_ShowString(30,220,500,24,24,"Time Interval:");
	//LCD_ShowString(150,160,200,24,24,"Hz");	      
	//LCD_ShowString(150,200,200,24,24,"\%");	      
	//LCD_ShowString(150,240,200,24,24,"ns");
  //LCD_ShowString(120,130,200,16,16,"Test");	
	//LCD_ShowString(60,190,200,16,16,"OUT VOL:0.000V");
  LCD_ShowString(30,140,200,24,24,"ADC RAW:");
	
	//DAC_SetChannel1Data(DAC_Align_12b_R, 0);//????0	   	      
	//delay_ms(1000);
	while(1)
	{
		adcx=Get_Adc(ADC_Channel_1);
		//LCD_ShowNum(150,140,adcx,4,24);
		//delay_ms(1000);
		LCD_DrawPoint(i++,adcx*480/4095);
		//LCD_Fill(i+30,0,i+31,480,WHITE);
		//LCD_DrawLine(i++,adcxx*480/4095,i,adcx*480/4095);
		//adcxx=adcx;
		if(i>800)
			i=0;
		
		
		
		
		
		
		
		
		
		
		/*
		dutyRatio_N=(data4*100.0)/(data3+data4);
		if(abs(dutyRatio_N-dutyRatio_L)>1.5)
		{
			dutyRatio=dutyRatio_N;
			dutyRatio_L=dutyRatio;
		}
		else
		{
			dutyRatio=dutyRatio_L*0.80+dutyRatio_N*0.20;
			dutyRatio_L=dutyRatio;
		}
		
		dutyRatio = 100 - dutyRatio; //Fix the ratio problem due to the change of variables.
		
		POINT_COLOR=BLUE;//设置字体为蓝色
		LCD_ShowxFloat(30,160,data1,0,10,24,0);
		LCD_ShowxFloat(30,200,dutyRatio,2,10,24,0);
		LCD_ShowxFloat(30,240,timeInterval,4,10,24,0);
		POINT_COLOR=RED;
		
		delay_us(1);*/
		//GPIO_SetBits(SPI_FLAG_PORT,SPI_FLAG);
		
		//Data_R=SPI1_ReadWriteByte(0xFE);
		
		//Data_F=Data_R >> 32;
		//Data_L=Data_R & 0x0FFFFFFFF;
		/*
		switch(Data_F)
		{
			case 1:
			{
				//LED1=!LED1;
				data1=Data_L;
				LCD_ShowxNum(240,140,data1,10,24,0);
				break;
			}
			case 2:
			{
				data2=Data_L;
				LCD_ShowxNum(240,160,data2,10,24,0);
				break;
			}
			case 3:
			{
				data3=Data_L;
				LCD_ShowxNum(240,180,data3,10,24,0);
				break;
			}
			case 4:
			{
				data4=Data_L;
				LCD_ShowxNum(240,200,data4,10,24,0);
				break;
			}
			case 5:
			{
				data5=Data_L;
				LCD_ShowxNum(240,220,data5,10,24,0);
				break;
			}
			case 6:
			{
				data6=Data_L;
				LCD_ShowxNum(240,240,data6,10,24,0);
				switch(data6)
					{
					case 1:
						{
							timeInterval=data5*20.0;break;
						}
					case 2:
						{
							timeInterval=data5*20/500.0;break;
						}
					case 3:
						{
							timeInterval=data5*20/5000.0;break;
						}
					}
					timeInterval_N=timeInterval;	//先给dutyRatio_N 运算后给dutyRatio显示
					if(abs(dutyRatio_N-dutyRatio_L)>5.0)
					{
						timeInterval=timeInterval_N;
						timeInterval_L=timeInterval;
					}
					else
					{
						timeInterval=timeInterval_L*0.80+timeInterval_N*0.20;
						timeInterval_L=timeInterval;
					}
					break;
			}
		}*/
		//GPIO_ResetBits(SPI_FLAG_PORT,SPI_FLAG); // flag = 0
	}									    
}	
/*
//fix include errors
void SPIx_Init(void)
{
  GPIO_InitTypeDef SPI_GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_SPI, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_SPI_FLAG, ENABLE);
	
  SPI_GPIO_InitStructure.GPIO_Pin =  SPI_MOSI;//MOSI
	SPI_GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	//SPI_GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	SPI_GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	SPI_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
  GPIO_Init(SPI_PORT, &SPI_GPIO_InitStructure);

	SPI_GPIO_InitStructure.GPIO_Pin = SPI_CS|SPI_SCLK|SPI_MISO;//CS,SCLK,MISO
  SPI_GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	SPI_GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	SPI_GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	//SPI_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
  GPIO_Init(SPI_PORT, &SPI_GPIO_InitStructure);	
	
	SPI_GPIO_InitStructure.GPIO_Pin = SPI_FLAG;//CS,SCLK,MISO
  SPI_GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	SPI_GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	SPI_GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	//SPI_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
  GPIO_Init(SPI_FLAG_PORT, &SPI_GPIO_InitStructure);	
}


uint64_t SPIx_SendReadByte36(uint64_t byte)
{
  uint64_t DataSend = byte; 
  uint64_t DataRead = 0;
  int i = 0;
  u8 SDI = 0;	
	//LED0=!LED0;
  GPIO_SetBits(SPI_PORT,SPI_CS);//cs = 1          
  delay_us(1);
  GPIO_ResetBits(SPI_PORT,SPI_CS);//cs = 0
	delay_us(1);
	
  for (i = 0; i < 36; i++)
  {
    GPIO_SetBits(SPI_PORT,SPI_SCLK);//sclk = 1    
    delay_us(1);
    if ((DataSend<<i)&0x800000000)
    {
      GPIO_SetBits(SPI_PORT,SPI_MISO); //output = 1 	
    }
    else
    {
      GPIO_ResetBits(SPI_PORT,SPI_MISO);//output = 0
    }
    
    DataRead <<= 1;
    GPIO_ResetBits(SPI_PORT,SPI_SCLK);//sclk = 0;
    delay_us(1);
    SDI = GPIO_ReadInputDataBit(SPI_PORT, SPI_MOSI);//read 
    if(SDI)
		{
      DataRead |= 0x0001;	
		}
    else
		{
			DataRead &= ~0x0001;
		}
  }
  GPIO_SetBits(SPI_PORT,SPI_CS); // cs = 1
	delay_us(1);
  return DataRead;    
}

uint64_t SPIx_SendReadByte16(uint64_t byte)
{
  uint64_t DataSend = byte; 
  uint64_t DataRead = 0;
  int i = 0;
  u8 SDI = 0;
  GPIO_SetBits(SPI_PORT,SPI_CS);//cs = 1
  delay_us(1000);
  GPIO_ResetBits(SPI_PORT,SPI_CS);//cs = 0
  delay_us(1);
  for (i = 0; i < 16; i++)
  {
    GPIO_SetBits(SPI_PORT,SPI_SCLK);//sclk = 1    
    delay_us(1);
    if ((DataSend<<i)&0x8000) 
    {
      GPIO_SetBits(SPI_PORT,SPI_MISO); //output = 1 
    }
    else
    {
      GPIO_ResetBits(SPI_PORT, SPI_MISO);//output = 0
    }
    
    DataRead <<= 1;
    GPIO_ResetBits(SPI_PORT, SPI_SCLK);//sclk = 0;
    delay_us(1);
    SDI = GPIO_ReadInputDataBit(SPI_PORT, SPI_MOSI);//read 
    if(SDI)
      DataRead |= 0x0001;
    else
    DataRead &= ~0x0001;
  }
  GPIO_SetBits(SPI_PORT,SPI_CS); // cs = 1
  delay_us(1);
  return DataRead;	
}
*/