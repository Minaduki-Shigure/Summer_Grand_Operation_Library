#ifndef __EXTI_H
#define __EXTI_H	 
#include "sys.h"  	
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

extern u8 new_signal_flag;
extern uint64_t data_f;
extern uint64_t Freq;
extern uint32_t Freq_cnt_1;
extern uint32_t Freq_cnt_2;
extern uint16_t Y_data[20];

void EXTIX_Init(void);	//�ⲿ�жϳ�ʼ��		 					    
#endif

























