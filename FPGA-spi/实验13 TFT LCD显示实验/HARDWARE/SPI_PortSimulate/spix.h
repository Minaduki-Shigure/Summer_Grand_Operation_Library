#ifndef __SPIX_H
#define __SPIX_H 			   
#include <sys.h>

#define SPI_PORT GPIOF
#define SPI_CS   GPIO_Pin_2
#define SPI_SCLK GPIO_Pin_4
#define SPI_MISO GPIO_Pin_6
#define SPI_MOSI GPIO_Pin_8
#define SPI_FLAG GPIO_Pin_7
#define RCC_SPI  RCC_AHB1Periph_GPIOF

void SPIx_Init(void);
uint64_t SPIx_SendReadByte36(uint64_t byte);
uint64_t SPIx_SendReadByte16(uint64_t byte);

#endif
