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
#include <math.h>
#include "ADF4351.h"
#include "PE4302.H"

//definations -->
#define XaxisHeight 12
#define YaxisHeight XaxisHeight

#define Workspace_x_max 500
#define Workspace_y_max 400

#define SPI_FLAG_PORT GPIOC	
#define SPI_FLAG 	GPIO_Pin_7
#define RCC_SPI_FLAG		RCC_AHB1Periph_GPIOC

//variables defination -->
double ADF4351VALUE;
extern int Enter_flag;
int menu_flag;
int i=0;
int X_pos=0;
double Y_to_draw=100;
int Data_in;

//function defination -->
u8 touchandgive(void);
u8	GT9147_Init(void);



void LCD_Menu(unsigned int row_num, unsigned int col_num, char* ptr, char** menuitem);
void AGC_FeedBack(float _x_);


int main(void)
{
	char mode, key_char;
	u16 PE4302VALUE_0=0;
	u16 PE4302VALUE_1=0;
	double input=0.0;
	unsigned char* input_s ;
	//char* menuitem[4]={"pattern1","pattern2"};
	GPIO_InitTypeDef SPI_GPIO_InitStructure;
	uint64_t Data=0;
	float Data_show1=0;
	int Data_show2=0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);
	uart_init(115200);
	reset_init();
	LCD_Init();
	ADF4351Init();
	PE_GPIO_Init();
	LCD_Display_Dir(1);
	LCD_DisplayOn();
	Adc_Init();
	//Init_KeyBoard_Port();
	//KeyBoard_Interrupt_Init();
  GT9147_Init();
	LCD_Clear(DARKBLUE);
	POINT_COLOR=RED;
	BACK_COLOR=DARKBLUE;
	ADF4351WriteFreq(40);
	SPI1_Init();	
	SPI1_SetSpeed(SPI_BaudRatePrescaler_2);
	
	RCC_AHB1PeriphClockCmd(RCC_SPI_FLAG, ENABLE);	
	SPI_GPIO_InitStructure.GPIO_Pin = SPI_FLAG;//CS,SCLK,MISO  
	SPI_GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	SPI_GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;	
	SPI_GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	//SPI_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;   
	GPIO_Init(SPI_FLAG_PORT, &SPI_GPIO_InitStructure);	
	
	
	
	/*LCD_Set_Window(0,0,800,480);
	POINT_COLOR=GRAY;
	LCD_ShowxString(30,20,210,32,32,(u8*)"STM32F4",1);
	LCD_ShowxString(30,60,272,32,32,(u8*)"80~100MHz Freq",1);*/
	
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
						
						
						
						
						
						//SPI通信
						GPIO_ResetBits(GPIOA,GPIO_Pin_3); // flag = 0	
						Data=SPI_SendReadByte8x5(0x00000002);
						GPIO_SetBits(GPIOA,GPIO_Pin_3); // flag = 1	
						Data_show1=(double)Data;
						LCD_ShowFloat(30,100,Data_show1,3,10,32);
						Data_show2=(int)Data;
						LCD_ShowNum(30,180,Data_show2,4,32);
		
						
						//触摸屏显示触摸位置
						GT9147_Scan(0);
					
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
						
						
						POINT_COLOR=WHITE;
						LCD_DrawPoint(X_pos++, Y_to_draw*Workspace_y_max);
						if(X_pos<Workspace_x_max-30){
							LCD_Fill(X_pos+30, 0, X_pos+30, Workspace_y_max, DARKBLUE);
							for(i=0; i<9; i++){
								LCD_DrawPoint(X_pos+30, 50*i);
							}		
						}
						else{
							LCD_Fill(X_pos+30-Workspace_x_max, 0, X_pos+30-Workspace_x_max, Workspace_y_max, DARKBLUE);
							for(i=0; i<9; i++){
								LCD_DrawPoint(X_pos+30-Workspace_x_max, 50*i);
							}		
						}
						if(X_pos==Workspace_x_max)
							X_pos=0;
	}
}


	
	
	
	//				case 3://PE_1
//				{
//					if(Enter_flag==1&&!menu_flag)
//					{
//						LCD_Fill(0,100,800,480,DARKBLUE);
//						LCD_Fill(300,0,800,100,DARKBLUE);
//						LCD_ShowxString(30,100,272,32,32,(u8*)"PE_1 Gain Attenuation    ",0);
//						LCD_ShowxString(160,180,272,32,32,(u8*)"dB",0);
//						if(input>63||input==0)input=63;
//						PE4302VALUE_0 = input;
//						LCD_ShowxNum(120,180,input,2,32,0);
//						PE4302_x_Set(PE4302VALUE_0, 0);
//					}
//				}break;
//				case 4://PE_2
//				{
//					if(Enter_flag==1&&!menu_flag)
//					{
//						LCD_Fill(0,100,800,480,DARKBLUE);
//						LCD_Fill(300,0,800,100,DARKBLUE);
//						LCD_ShowxString(30,100,272,32,32,(u8*)"PE_2 Gain Attenuation    ",0);
//						LCD_ShowxString(160,180,272,32,32,(u8*)"dB",0);
//						if(input>63||input==0) input=63;
//						PE4302VALUE_1 = input;
//						LCD_ShowxNum(120,180,input,2,32,0);
//						PE4302_x_Set(PE4302VALUE_1, 1);
//					}
//				}break;
			
//			}
//			input_s = input_string_s(30,400);
//			key_char = input_s[0];
//			input = Char_2_Double(input_s);
//			if(key_char=='B'&&Enter_flag==1) {menu_flag=1; input=0;}
//		}
//}



//void LCD_Menu(unsigned int row_num, unsigned int col_num, char* ptr, char** menuitem)
//{
//	unsigned int delta_x, delta_y;
//	unsigned char ptr_temp, ptr_last, certain_cursor=0;
//	int i,j,i_last,j_last,i_temp,j_temp;//j colum   i row
//	u16 point_color_temp;
//	char key_char,count;
//	ptr_temp=ptr_last=(*ptr-1)%(row_num*col_num)+1;
//	point_color_temp=POINT_COLOR;
//	POINT_COLOR=WHITE;
//	LCD_Clear(BLUE);
//	if(lcddev.dir==0){//vertical
//		delta_x = SSD_VER_RESOLUTION/col_num;
//		delta_y = SSD_HOR_RESOLUTION/row_num;
//	}else{//horizontal
//		delta_x = SSD_HOR_RESOLUTION/col_num;
//		delta_y = SSD_VER_RESOLUTION/row_num;
//	}
//	for(i=0,count=0;i<col_num;i++){
//		for(j=0;j<row_num;j++){
//			LCD_Fill(i*delta_x,j*delta_y,(i+1)*delta_x-4,(j+1)*delta_y-4,GRAY);
//			LCD_ShowString(i*delta_x+6,j*delta_y+delta_y/2,272,32,32,(u8*)menuitem[count++]);
//		}
//	}
//	i_temp = (ptr_temp-1)/row_num;
//	j_temp = (ptr_temp-1)%row_num;
//	LCD_Fill(i_temp*delta_x,j_temp*delta_y,(i_temp+1)*delta_x-4,(j_temp+1)*delta_y-4,BLUE);
//	LCD_ShowString(i_temp*delta_x+6,j_temp*delta_y+delta_y/2,272,32,32,(u8*)menuitem[ptr_temp-1]);
//	while(1){
//		ptr_last = ptr_temp;
//		key_char=input_char();
//		if(key_char=='2'){//up
//			ptr_temp -= 1;
//			if(!(ptr_temp%row_num))ptr_temp = ptr_temp+row_num;
//			//ptr_temp%=(row_num*col_num);
//		}else if(key_char=='8'){//down
//			if(!(ptr_temp%row_num))ptr_temp = ptr_temp+1-row_num;
//			else ptr_temp = ptr_temp+1;
//			//ptr_temp%=(row_num*col_num);
//		}else if(key_char=='4'){//left
//			if(ptr_temp>row_num)ptr_temp -= row_num;
//			else ptr_temp += (col_num-1)*row_num;
//		}else if(key_char=='6'){//right
//			if(ptr_temp<=(col_num-1)*row_num)ptr_temp += row_num;
//			else ptr_temp -=(col_num-1)*row_num;
//		}else if(key_char=='5'){
//			certain_cursor = 1;
//		}else if(key_char=='*')break;
//		//if(ptr_temp==0)LCD_Clear(BLUE);
//		i_last = (ptr_last-1)/row_num;
//		j_last = (ptr_last-1)%row_num;
//		i_temp = (ptr_temp-1)/row_num;
//		j_temp = (ptr_temp-1)%row_num;
//		if(certain_cursor){
//			POINT_COLOR=RED;
//			LCD_DrawLine(i_temp*delta_x+4, j_temp*delta_y+4, i_temp*delta_x+4, (j_temp+1)*delta_y-4);
//			LCD_DrawLine(i_temp*delta_x+5, j_temp*delta_y+5, i_temp*delta_x+5, (j_temp+1)*delta_y-5);
//			LCD_DrawLine(i_temp*delta_x+6, j_temp*delta_y+6, i_temp*delta_x+6, (j_temp+1)*delta_y-6);
//			LCD_DrawLine(i_temp*delta_x+4, (j_temp+1)*delta_y-4, (i_temp+1)*delta_x-4, (j_temp+1)*delta_y-4);
//			LCD_DrawLine(i_temp*delta_x+5, (j_temp+1)*delta_y-5, (i_temp+1)*delta_x-5, (j_temp+1)*delta_y-5);
//			LCD_DrawLine(i_temp*delta_x+6, (j_temp+1)*delta_y-6, (i_temp+1)*delta_x-6, (j_temp+1)*delta_y-6);
//			LCD_DrawLine((i_temp+1)*delta_x-4, (j_temp+1)*delta_y-4, (i_temp+1)*delta_x-4, j_temp*delta_y+4);
//			LCD_DrawLine((i_temp+1)*delta_x-5, (j_temp+1)*delta_y-5, (i_temp+1)*delta_x-5, j_temp*delta_y+5);
//			LCD_DrawLine((i_temp+1)*delta_x-6, (j_temp+1)*delta_y-6, (i_temp+1)*delta_x-6, j_temp*delta_y+6);
//			LCD_DrawLine((i_temp+1)*delta_x-4, j_temp*delta_y+4, i_temp*delta_x+4, j_temp*delta_y+4);
//			LCD_DrawLine((i_temp+1)*delta_x-5, j_temp*delta_y+5, i_temp*delta_x+5, j_temp*delta_y+5);
//			LCD_DrawLine((i_temp+1)*delta_x-6, j_temp*delta_y+6, i_temp*delta_x+6, j_temp*delta_y+6);
//			POINT_COLOR=point_color_temp;
//			*ptr=ptr_temp;
//			certain_cursor=0;
//		}else if(ptr_last!=ptr_temp){
//			LCD_Fill(i_last*delta_x,j_last*delta_y,(i_last+1)*delta_x-4,(j_last+1)*delta_y-4,GRAY);
//			LCD_ShowString(i_last*delta_x+6,j_last*delta_y+delta_y/2,272,32,32,(u8*)menuitem[ptr_last-1]);
//			LCD_Fill(i_temp*delta_x,j_temp*delta_y,(i_temp+1)*delta_x-4,(j_temp+1)*delta_y-4,BLUE);
//			LCD_ShowString(i_temp*delta_x+6,j_temp*delta_y+delta_y/2,272,32,32,(u8*)menuitem[ptr_temp-1]);
//		}
//		ptr_last = ptr_temp;
//	}
//	
//	menu_flag=0;
//	LCD_Clear(DARKBLUE);
//	POINT_COLOR=point_color_temp;
//	//LCD_ShowxFloat(30,200,*ptr,1,10,32,0);
//}

////void AGC_FeedBack(float _x_)
////{
////	double val;
////	double val_x_;
////	double val_real;
////	u16 adcx;
////	u8 Set_db;
////	static u8 PE_0_DB=0;
////	static u8 PE_1_DB=0;
////	u8 PE_DB_a=0;
////	u8 PE_DB_b=0;
////	double PE_delta=0;
////	static u8 PE_temp=0;
////	adcx=Get_Adc_Average(ADC_Channel_1,20,2);
////	val=adcx*3.3/4069;
////	val_real=pow(2.7182856,val/0.209)/160.7;
////	val_x_=log10(160.7*_x_)/log10(2.7182856)*0.209;
////	LCD_Set_Window(0,0,800,480);
////	POINT_COLOR=WHITE;
////	LCD_ShowString(30,40,210,32,24,(u8*)"STM32F4");
////	LCD_ShowString(30,80,272,32,24,(u8*)"Get_adc");
////	LCD_ShowNum(110,80,adcx,20,24);//显示AD数值
////	LCD_ShowxFloat(300,120,val,3,10,24,0);
////	LCD_ShowxFloat(400,120,val_real,3,10,24,0);
////	//LCD_ShowNum(90,120,val_real,20,24);//显示检波电压值
////	Set_db=40*log10(val);
////	LCD_ShowString(30,160,210,32,24,(u8*)"Set_db");
////	LCD_ShowNum(110,160,Set_db,20,24);
////	LCD_ShowString(30,200,300,32,24,(u8*)"PE_1_DB");
////	LCD_ShowNum(110,200,PE_0_DB,20,24);
////	LCD_ShowString(30,240,300,32,24,(u8*)"PE_2_DB");
////	LCD_ShowNum(110,240,PE_1_DB,20,24);
////	LCD_ShowString(30,280,272,32,24,(u8*)"Expectation");
////	LCD_ShowxFloat(300,280,_x_,3,10,24,0);//显示AD数值
////	LCD_ShowxFloat(300,320,val_x_,3,10,24,0);
////	
////	if(!(val_x_-0.05<val&&val<val_x_+0.03)){
////		PE_delta=20*(val-val_x_);
////		PE_temp=PE_temp+PE_delta>120?120:(PE_temp+PE_delta);
////		LCD_ShowxFloat(300,360,PE_temp,3,10,24,0);
////		LCD_ShowxFloat(400,360,PE_delta,3,10,24,0);
////		if(PE_temp<40){
////			if(PE_DB_a<20){PE_DB_a=PE_temp;PE_DB_b=0;}
////			else{PE_DB_a=20;PE_DB_b=PE_temp-20;}
////		}
////		else if(PE_temp<80){
////			if(PE_DB_a<40){PE_DB_a=PE_temp-20;PE_DB_b=20;}
////			else{PE_DB_a=40;PE_DB_b=PE_temp-40+20;}
////		}
////		else{
////			if(PE_DB_a<60){PE_DB_a=PE_temp-40;PE_DB_b=40;}
////			else{PE_DB_a=60;PE_DB_b=PE_temp-60+40;}
////		}
////		if(val>val_x_+0.03){
////			PE_0_DB=PE_DB_a>60?60:PE_DB_a;
////			PE_1_DB=PE_DB_b>60?60:PE_DB_b;
////		}
////		else{
////			PE_1_DB=PE_DB_a>60?60:PE_DB_a;
////			PE_0_DB=PE_DB_b>60?60:PE_DB_b;			
////		}
////		PE4302_x_Set(PE_0_DB,0);
////		PE4302_x_Set(PE_1_DB,1);
////	}
////	
