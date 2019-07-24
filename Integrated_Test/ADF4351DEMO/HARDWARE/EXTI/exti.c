#include "exti.h"
#include "delay.h"
#include "led.h"
#include "spi.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//外部中断 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

uint64_t SPI_NULL=0x0000000000000000;
uint64_t Data_R;

//外部中断0服务程序
void EXTI0_IRQHandler(void)
{
	int iii=0;
	
	for(iii=0;iii<28;iii++)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_3);//flag = 1;
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);//cs = 0;
		Data_R=SPI1_ReadWriteByte(0xA81A);
		//Data_R=SPIx_SendReadByte36(0xF000F000F);
		switch(Data_R&0xFF00)
		{
			case 0x0100:Y_data[0]=Data_R&0x00FF;break;
			case 0x0200:Y_data[1]=Data_R&0x00FF;break;
			case 0x0300:Y_data[2]=Data_R&0x00FF;break;
			case 0x0400:Y_data[3]=Data_R&0x00FF;break;
			case 0x0500:Y_data[4]=Data_R&0x00FF;break;
			case 0x0600:Y_data[5]=Data_R&0x00FF;break;
			case 0x0700:Y_data[6]=Data_R&0x00FF;break;
			case 0x0800:Y_data[7]=Data_R&0x00FF;break;
			case 0x0900:Y_data[8]=Data_R&0x00FF;break;
			case 0x0A00:Y_data[9]=Data_R&0x00FF;break;
			case 0x0B00:Y_data[10]=Data_R&0x00FF;break;
			case 0x0C00:Y_data[11]=Data_R&0x00FF;break;
			case 0x0D00:Y_data[12]=Data_R&0x00FF;break;
			case 0x0E00:Y_data[13]=Data_R&0x00FF;break;
			case 0x0F00:Y_data[14]=Data_R&0x00FF;break;
			case 0x1000:Y_data[15]=Data_R&0x00FF;break;
			case 0x1100:Y_data[16]=Data_R&0x00FF;break;
			case 0x1200:Y_data[17]=Data_R&0x00FF;break;
			case 0x1300:Y_data[18]=Data_R&0x00FF;break;
			case 0x1400:Y_data[19]=Data_R&0x00FF;break;
			case 0x1500:Freq_cnt_1|=Data_R&0x00FF;break;
			case 0x1600:Freq_cnt_1|=(Data_R&0x00FF)<<8;break;
			case 0x1700:Freq_cnt_1|=(Data_R&0x00FF)<<16;break;
			case 0x1800:Freq_cnt_1|=(Data_R&0x00FF)<<24;break;
			case 0x1900:Freq_cnt_2|=Data_R&0x00FF;break;
			case 0x1A00:Freq_cnt_2|=(Data_R&0x00FF)<<8;break;
			case 0x1B00:Freq_cnt_2|=(Data_R&0x00FF)<<16;break;
			case 0x1C00:Freq_cnt_2|=(Data_R&0x00FF)<<24;break;
			default:break;
		}
		data_f++;
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);//flag = 0;
		GPIO_SetBits(GPIOA,GPIO_Pin_4);//cs = 1;
	}
	new_signal_flag = 1;
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
}	

//外部中断初始化程序
//初始化PA0为中断输入.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 连接到中断线0
	
  /* 配置EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE0
  EXTI_Init(&EXTI_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//FLAG对应引脚PA0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA0

	//in order to measure the period of the function
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//FLAG对应引脚PF10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输入模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIOF10
	GPIO_SetBits(GPIOF,GPIO_Pin_10);
	
}


