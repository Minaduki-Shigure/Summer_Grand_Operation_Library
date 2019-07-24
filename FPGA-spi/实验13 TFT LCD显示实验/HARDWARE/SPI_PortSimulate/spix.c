#include "spix.h"
#include "delay.h"

void SPIx_Init(void)
{
  GPIO_InitTypeDef SPI_GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_SPI, ENABLE);
	
  SPI_GPIO_InitStructure.GPIO_Pin =  SPI_MOSI ;//MOSI
  SPI_GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN;
	SPI_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  SPI_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	SPI_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(SPI_PORT, &SPI_GPIO_InitStructure);
	
	SPI_GPIO_InitStructure.GPIO_Pin = SPI_CS|SPI_SCLK|SPI_MISO|SPI_FLAG;//CS,SCLK,MISO
  SPI_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	SPI_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  SPI_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	SPI_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(SPI_PORT, &SPI_GPIO_InitStructure);	
}


uint64_t SPIx_SendReadByte36(uint64_t byte)
{
  uint64_t DataSend = byte; 
  uint64_t DataRead = 0;
  int i = 0;
  u8 SDI = 0;
  GPIO_SetBits(SPI_PORT,SPI_CS);//cs = 1
  delay_us(1000);
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
