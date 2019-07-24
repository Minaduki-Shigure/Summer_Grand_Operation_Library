#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"
#include "spi.h"
#include "key.h"
#include "LCD12864.h"
//#include "KeyBoard.h"
#include "EXTI.h"
#include <math.h>
#include "gt9147.h"
#include "touch.h"
#include "ctiic.h"
#include "string.h" 

//definations -->
#define XaxisHeight 12
#define YaxisHeight XaxisHeight

#define Workspace_x_max 500
#define Workspace_y_max 400

#define MODE_CHANGE_FLAG 0

#define Y_MAXIMUM 20

//variables defination -->
extern int Enter_flag;
int menu_flag;
int Draw_finish_flag=1;
int i=0;
int X_pos=0;
int counter=0;
float Y_to_draw=100;
float Y_last=100;

uint64_t data_f=0;
u8 new_signal_flag=0;
uint32_t Freq_cnt_1=0;
uint32_t Freq_cnt_2=0;
uint64_t Freq=0;
uint16_t Y_data[20]={0};

//function defination -->
u8 touchandgive(void);
u8	GT9147_Init(void);
void Display_Wave(void);

int main(void)
{
	char mode, key_char;
	double input=0.0;
	unsigned char* input_s ;
	//char* menuitem[4]={"pattern1","pattern2"};
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);
	uart_init(115200);
	reset_init();
	LCD_Init();
	LCD_Display_Dir(1);
	LCD_DisplayOn();
	Adc_Init();
	//Init_KeyBoard_Port();
	//KeyBoard_Interrupt_Init();
  GT9147_Init();
	LCD_Clear(DARKBLUE);
	POINT_COLOR=RED;
	BACK_COLOR=DARKBLUE;
	SPI1_Init();	
	SPI1_SetSpeed(SPI_BaudRatePrescaler_64);
	EXTIX_Init();
	
	POINT_COLOR=WHITE;
//	menu_flag = 1;
//	mode=1;
		while(1)
		{
//		if(menu_flag == 1){
//			LCD_Menu(1, 1, &mode, menuitem);
//			
//			Enter_flag=1;
//		}
//		else{
//			switch(mode)
//			{
//				case 1://pattern1
//				{
//					
//					if(!menu_flag)
//					{
//						
//						LCD_DrawRectangle(20, 20, 140, 220 );
//						LCD_DrawRectangle(180, 20, 300, 220 );
//						LCD_DrawRectangle(340, 20, 460, 220 );
//						LCD_DrawRectangle(500, 20, 620, 220 );
//						LCD_DrawRectangle(660, 20, 780, 220 );
//						LCD_DrawRectangle(20, 260, 140, 460 );
//						LCD_DrawRectangle(180, 260,300, 460 );
//						LCD_DrawRectangle(340, 260, 460, 460 );
//						LCD_DrawRectangle(500, 260, 620, 460 );
//						LCD_DrawRectangle(660, 260, 780, 460 );
//						
//						LCD_ShowxString(30,125,100,24,24,(u8*)"20ms/div",0);
//						LCD_ShowxString(190,125,100,24,24,(u8*)"200us/div",0);
//						LCD_ShowxString(350,125,100,24,24,(u8*)"2us/div",0);
//						LCD_ShowxString(510,125,100,24,24,(u8*)"100ns/div",0);
//						LCD_ShowxString(670,125,100,24,24,(u8*)"storage",0);
//						LCD_ShowxString(30,365,100,24,24,(u8*)"1V/div",0);
//						LCD_ShowxString(190,365,100,24,24,(u8*)"0.1V/div",0);
//						LCD_ShowxString(350,365,100,24,24,(u8*)"2mV/div",0);
//						LCD_ShowxString(510,365,100,24,24,(u8*)"trigger",0);	
//					}
//				}break;
//				case 2://pattern2
//				{
//					if(!menu_flag)
//					{
//						Enter_flag=0;
//						LCD_Fill(0,400,500,480,DARKBLUE);
//						LCD_Fill(500,0,800,480,DARKBLUE);
						
						
//						//SPI通信Template
//						GPIO_ResetBits(GPIOA,GPIO_Pin_3); // flag = 0	
//						Data=SPI_SendReadByte8x5(0x00000002);
//						GPIO_SetBits(GPIOA,GPIO_Pin_3); // flag = 1	
//						Data_show1=(double)Data;
//						LCD_ShowFloat(30,100,Data_show1,3,10,32);
//						Data_show2=(int)Data;
//						LCD_ShowNum(30,180,Data_show2,4,32);
		
					
						//画矩形框
						LCD_DrawRectangle(510, 10, 640, 110 );
						LCD_DrawRectangle(660, 10, 790, 110 );
						LCD_DrawRectangle(510,130, 640, 230 );
						LCD_DrawRectangle(660,130, 790, 230 );
						LCD_DrawRectangle(510,250, 640, 350 );
						LCD_DrawRectangle(660,250, 790, 350 );
						LCD_DrawRectangle(510,370, 640, 470 );
						LCD_DrawRectangle(660,370, 790, 470 );//右两列
						
						LCD_DrawRectangle(30,420, 160, 470 );
						LCD_DrawRectangle(190,420, 320, 470 );
						LCD_DrawRectangle(350,420, 480, 470 );//下一行
						
						//示波器按键显示
						LCD_ShowxString(530,60,100,24,24,(u8*)"1V/div",0);
						LCD_ShowxString(690,60,100,24,24,(u8*)"20ms/div",0);
						LCD_ShowxString(530,180,100,24,24,(u8*)"0.1V/div",0);
						LCD_ShowxString(670,180,100,24,24,(u8*)"200us/div",0);
						LCD_ShowxString(530,300,100,24,24,(u8*)"2mV/div",0);
						LCD_ShowxString(690,300,100,24,24,(u8*)"2us/div",0);
						LCD_ShowxString(530,420,100,24,24,(u8*)"auto",0);
						LCD_ShowxString(670,420,100,24,24,(u8*)"100ns/div",0);
						
						LCD_ShowxString(60,445,100,24,24,(u8*)"trigger",0);
						LCD_ShowxString(220,445,100,24,24,(u8*)"display",0);
						LCD_ShowxString(380,445,100,24,24,(u8*)"storage",0);
						
						//示波器界面画格
						LCD_DrawLine(0, 0, 500, 0);
						LCD_DrawLine(0, 50, 500, 50);
						LCD_DrawLine(0, 100, 500, 100);
						LCD_DrawLine(0, 150, 500, 150);
						LCD_DrawLine(0, 200, 500, 200);
						LCD_DrawLine(0, 250, 500, 250);
						LCD_DrawLine(0, 300, 500, 300);
						LCD_DrawLine(0, 350, 500, 350);
						LCD_DrawLine(0, 400, 500, 400);					//横线
						
						LCD_DrawLine(0, 0, 0, 400);
						LCD_DrawLine(50, 0, 50, 400);
						LCD_DrawLine(100, 0, 100, 400);
						LCD_DrawLine(150, 0, 150, 400);
						LCD_DrawLine(200, 0, 200, 400);
						LCD_DrawLine(250, 0, 250, 400);
						LCD_DrawLine(300, 0, 300, 400);
						LCD_DrawLine(350, 0, 350, 400);
						LCD_DrawLine(400, 0, 400, 400);
						LCD_DrawLine(450, 0, 450, 400);
						LCD_DrawLine(500, 0, 500, 400);					//竖线
												
						//Test data
						//for(i=0; i<20; i++)
						//{
						//	Y_data[i]=200*i;
						//}
												
						while(1)
						{
														
						//设置电压单位
						while(tp_dev.x[i]>10&&tp_dev.x[i]<110&&tp_dev.y[i]>160&&tp_dev.y[i]<290)
						{
							Display_Wave();
							GT9147_Scan(0);
							POINT_COLOR=RED;
							LCD_ShowxString(530,60,100,24,24,(u8*)"1V/div",0);
						}					//1V/div
						
						//触摸屏显示触摸位置
						POINT_COLOR=WHITE;
						LCD_ShowxString(530,60,100,24,24,(u8*)"1V/div",0);
						GT9147_Scan(0);
							
								
								
//							if(new_signal_flag)
//							{

//								LCD_Fill(30,170,200,200,BLUE);
//								LCD_Fill(30,280,200,460,BLUE);
//								LCD_Fill(230,80,400,460,BLUE);
//								LCD_Fill(430,80,600,200,BLUE);
//								
//								Freq = data_f;	//Test data
//								
//								LCD_ShowxFloat(30,170,Freq,2,10,32,1);
//								LCD_ShowxFloat(30,280,Y_data[0],2,10,32,1);
//								LCD_ShowxFloat(30,310,Y_data[1],2,10,32,1);
//								LCD_ShowxFloat(30,340,Y_data[2],2,10,32,1);
//								LCD_ShowxFloat(30,370,Y_data[3],2,10,32,1);
//								LCD_ShowxFloat(30,400,Y_data[4],2,10,32,1);
//								LCD_ShowxFloat(30,430,Y_data[5],2,10,32,1);
//								LCD_ShowxFloat(230,80,Y_data[6],2,10,32,1);
//								LCD_ShowxFloat(230,110,Y_data[7],2,10,32,1);
//								LCD_ShowxFloat(230,140,Y_data[8],2,10,32,1);
//								LCD_ShowxFloat(230,170,Y_data[9],2,10,32,1);
//								LCD_ShowxFloat(230,200,Y_data[10],2,10,32,1);
//								LCD_ShowxFloat(230,230,Y_data[11],2,10,32,1);
//								LCD_ShowxFloat(230,280,Y_data[12],2,10,32,1);
//								LCD_ShowxFloat(230,310,Y_data[13],2,10,32,1);
//								LCD_ShowxFloat(230,340,Y_data[14],2,10,32,1);
//								LCD_ShowxFloat(230,370,Y_data[15],2,10,32,1);
//								LCD_ShowxFloat(230,400,Y_data[16],2,10,32,1);
//								LCD_ShowxFloat(230,430,Y_data[17],2,10,32,1);
//								LCD_ShowxFloat(430,80,Y_data[18],2,10,32,1);
//								LCD_ShowxFloat(430,110,Y_data[19],2,10,32,1);
	
//								new_signal_flag = 0;
//								
//								Y_last=Y_to_draw;
//								Y_to_draw=(float)Y_data[X_pos%20]/Y_MAXIMUM;
//								
//								POINT_COLOR=YELLOW;
//								//LCD_DrawPoint(X_pos++, Y_to_draw*Workspace_y_max);
//								LCD_DrawLine(X_pos, Y_last*Workspace_y_max, X_pos+1, Y_to_draw*Workspace_y_max);
//								X_pos++;
//								POINT_COLOR=WHITE;
//								
//								if(X_pos<Workspace_x_max-30){
//									LCD_Fill(X_pos+30, 0, X_pos+30, Workspace_y_max, DARKBLUE);
//									if(!((X_pos+30)%50))
//									{
//										LCD_DrawLine(X_pos+30, 0, X_pos+30, Workspace_y_max);
//									}
//									else
//									{
//										for(i=0; i<9; i++)
//										{
//											LCD_DrawPoint(X_pos+30, 50*i);
//										}	
//									}									
//								}
//								else{
//									LCD_Fill(X_pos+30-Workspace_x_max, 0, X_pos+30-Workspace_x_max, Workspace_y_max, DARKBLUE);
//									if(!((X_pos+30-Workspace_x_max)%50))
//									{
//										LCD_DrawLine(X_pos+30-Workspace_x_max, 0, X_pos+30-Workspace_x_max, Workspace_y_max);
//									}
//									else
//									{
//										for(i=0; i<9; i++)
//										{
//											LCD_DrawPoint(X_pos+30-Workspace_x_max, 50*i);
//										}	
//									}									
//								}
//								if(X_pos==Workspace_x_max)
//								{
//									Draw_finish_flag=1;
//									X_pos=0;
//								}
								if(MODE_CHANGE_FLAG)
									break;
//							}
						}
	}
}
void Display_Wave(void)
{
	int i,y1,y2;
	double display[20];
	LCD_Fill(0,0,Workspace_x_max,Workspace_y_max,DARKBLUE);
	POINT_COLOR=WHITE;
	LCD_DrawLine(0, 0, 500, 0);
	LCD_DrawLine(0, 50, 500, 50);
	LCD_DrawLine(0, 100, 500, 100);
	LCD_DrawLine(0, 150, 500, 150);
	LCD_DrawLine(0, 200, 500, 200);
	LCD_DrawLine(0, 250, 500, 250);
	LCD_DrawLine(0, 300, 500, 300);
	LCD_DrawLine(0, 350, 500, 350);
	LCD_DrawLine(0, 400, 500, 400);					//横线
	
	LCD_DrawLine(0, 0, 0, 400);
	LCD_DrawLine(50, 0, 50, 400);
	LCD_DrawLine(100, 0, 100, 400);
	LCD_DrawLine(150, 0, 150, 400);
	LCD_DrawLine(200, 0, 200, 400);
	LCD_DrawLine(250, 0, 250, 400);
	LCD_DrawLine(300, 0, 300, 400);
	LCD_DrawLine(350, 0, 350, 400);
	LCD_DrawLine(400, 0, 400, 400);
	LCD_DrawLine(450, 0, 450, 400);
	LCD_DrawLine(500, 0, 500, 400);					//竖线
	POINT_COLOR=RED;
	for(i=0; i<20; i++)
	{
		display[i]=Y_data[i]*10/256-5;								//ange to voltage
	}
	for(i=0; i<20; i++)
	{
		display[i]=(10-display[i])*20;							//ange to coordinate
	}
	y1=display[0];
	LCD_DrawPoint(0,y1);  //画出了第一个点
	for(counter=0;counter<10;counter++)
	{
		for(i=0; i<20; i++)
		{
			y2=display[i];
			LCD_DrawLine(2*i+50*counter,y1,2*(i+1)+50*counter,y2);	
			y1 = y2;
			delay_ms(7);
		}
			
	}
}