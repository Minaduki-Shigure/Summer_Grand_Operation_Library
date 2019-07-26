#include "exti.h"
#include "delay.h"
#include "led.h"
#include "spi.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//�ⲿ�ж� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

uint64_t SPI_NULL=0x0000000000000000;
uint64_t Data_R;

//�ⲿ�ж�0�������
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
			case 0x0100:data[0]=Data_R&0x00FF;break;
			case 0x0200:data[1]=Data_R&0x00FF;break;
			case 0x0300:data[2]=Data_R&0x00FF;break;
			case 0x0400:data[3]=Data_R&0x00FF;break;
			case 0x0500:data[4]=Data_R&0x00FF;break;
			case 0x0600:data[5]=Data_R&0x00FF;break;
			case 0x0700:data[6]=Data_R&0x00FF;break;
			case 0x0800:data[7]=Data_R&0x00FF;break;
			case 0x0900:data[8]=Data_R&0x00FF;break;
			case 0x0A00:data[9]=Data_R&0x00FF;break;
			case 0x0B00:data[10]=Data_R&0x00FF;break;
			case 0x0C00:data[11]=Data_R&0x00FF;break;
			case 0x0D00:data[12]=Data_R&0x00FF;break;
			case 0x0E00:data[13]=Data_R&0x00FF;break;
			case 0x0F00:data[14]=Data_R&0x00FF;break;
			case 0x1000:data[15]=Data_R&0x00FF;break;
			case 0x1100:data[16]=Data_R&0x00FF;break;
			case 0x1200:data[17]=Data_R&0x00FF;break;
			case 0x1300:data[18]=Data_R&0x00FF;break;
			case 0x1400:data[19]=Data_R&0x00FF;break;
			case 0x1500:data[20]=Data_R&0x00FF;break;
			case 0x1600:data[21]=Data_R&0x00FF;break;
			case 0x1700:data[22]=Data_R&0x00FF;break;
			case 0x1800:data[23]=Data_R&0x00FF;break;
			case 0x1900:data[24]=Data_R&0x00FF;break;
			case 0x1A00:data[25]=Data_R&0x00FF;break;
			case 0x1B00:data[26]=Data_R&0x00FF;break;
			case 0x1C00:data[27]=Data_R&0x00FF;break;
			default:break;
		}
		data_f++;
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);//flag = 0;
		GPIO_SetBits(GPIOA,GPIO_Pin_4);//cs = 1;
	}
	new_signal_flag = 1;
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ 
}	

//�ⲿ�жϳ�ʼ������
//��ʼ��PA0Ϊ�ж�����.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 ���ӵ��ж���0
	
  /* ����EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش��� 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE0
  EXTI_Init(&EXTI_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//FLAG��Ӧ����PA0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA0

	//in order to measure the period of the function
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//FLAG��Ӧ����PF10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//����
  GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��GPIOF10
	GPIO_SetBits(GPIOF,GPIO_Pin_10);
	
}


