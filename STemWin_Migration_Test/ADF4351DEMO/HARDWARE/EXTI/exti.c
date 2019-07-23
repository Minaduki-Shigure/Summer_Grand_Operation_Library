#include "exti.h"
#include "led.h"
#include "lcd.h"
#include "delay.h"
#include "usart.h"
#include "spix.h"
#include "usart.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//外部中断 驱动代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/12/01  
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved	  
////////////////////////////////////////////////////////////////////////////////// 	  
 
 
//uint64_t SPI_NULL=0x0000000000000000;
//uint64_t Data_R;

//外部中断初始化函数
//void EXTIX_Init(void)
//{ 
// 	  EXTI_InitTypeDef EXTI_InitStructure;
// 	  NVIC_InitTypeDef NVIC_InitStructure;

//  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟

//    //GPIO A1 中断线以及中断初始化配置
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);

//  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//上升沿触发
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
// 
//  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
//}

 
//void EXTI1_IRQHandler(void)
//{
//	GPIO_SetBits(SPI_PORT, SPI_FLAG);//flag = 1;
//	
//	LED0=!LED0;
//	Data_R=SPIx_SendReadByte36(0xF0000001E);
//	if((Data_R&0x100000000)==0x100000000)
//	{
//		LED1=!LED1;
//		data1=Data_R&011111111;
//	}
//	if((Data_R&0x200000000)==0x200000000)
//	{
//		data2=Data_R&011111111;
//		LED1=!LED1;
//	}
//	if((Data_R&0x300000000)==0x300000000)
//	{
//		data3=Data_R&011111111;
//		LED1=!LED1;
//	}
//	if((Data_R&0x500000000)==0x500000000)
//	{
//		data4=Data_R&011111111;
//		LED1=!LED1;
//	}
//	
//	GPIO_ResetBits(SPI_PORT, SPI_FLAG);//flag = 0;
//	EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE0上的中断标志位 
//}

//浮点型转字符串并显示
//void fprint(float t,u8 d,u8 y)
//{
//	u8 num[15]={0},num1[15]={0};
//	u8 i=0,c=0;
//	long temp=0;

//	for(i=0;i<d;i++) t*=10;
//	temp=t;
//	if(temp==0) num1[0]='0';
//	else
//	{
//		if(temp<0) {num1[0]='-'; temp=-temp;}
//		else num1[0]='+';
//		i=0;
//		while(temp>0)
//			{num[i]=temp%10+48;temp/=10;i++;}
//		c=i-1;
//		if(d==0||d>8) for(i=1;i<=c+1;i++) num1[i]=num[c-i+1];
//		else if(d<=c)
//		{
//			for(i=1;i<=c-d+1;i++) num1[i]=num[c-i+1];
//			num1[c-d+2]='.';
//			for(i=c-d+3;i<=c+2;i++) num1[i]=num[c-i+2];
//		}
//		else
//		{
//			num1[1]='0';
//			num1[2]='.';
//			for(i=3;i<d-c+2;i++) num1[i]='0';
//			for(i=d-c+2;i<=d+2;i++) num1[i]=num[d-i+2];
//		}
//	}
//	LCD_ShowString(30,y,200,16,16,num1);
//	sendstring1(num1);
//}
