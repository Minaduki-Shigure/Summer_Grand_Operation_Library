#include "exti.h"
#include "led.h"
#include "lcd.h"
#include "delay.h"
#include "usart.h"
#include "spix.h"
#include "usart.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//�ⲿ�ж� ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/01  
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved	  
////////////////////////////////////////////////////////////////////////////////// 	  
 
 
//uint64_t SPI_NULL=0x0000000000000000;
//uint64_t Data_R;

//�ⲿ�жϳ�ʼ������
//void EXTIX_Init(void)
//{ 
// 	  EXTI_InitTypeDef EXTI_InitStructure;
// 	  NVIC_InitTypeDef NVIC_InitStructure;

//  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��

//    //GPIO A1 �ж����Լ��жϳ�ʼ������
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);

//  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//�����ش���
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
// 
//  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ���ⲿ�ж�ͨ��
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
//  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
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
//	EXTI_ClearITPendingBit(EXTI_Line1); //���LINE0�ϵ��жϱ�־λ 
//}

//������ת�ַ�������ʾ
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
