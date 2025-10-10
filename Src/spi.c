#include "spi.h"

void spi_init(void){
    RCC->AHB1ENR |= (1u<<0);
    RCC->APB1ENR |= (1u<<12);

    GPIOA->MODER &= ~(3u<<10);
    GPIOA->MODER &= ~(3u<<14);

    GPIOA->MODER |= (2u<<10);
    GPIOA->MODER |= (2u<<14);

    GPIOA->AFR[0] |= (5u<<20);
    GPIOA->AFR[0] |= (5u<<28);

    GPIOA->MODER |= (1u<<8);
    GPIOA->MODER |= (1u<<4);
    GPIOA->MODER |= (1u<<6);

    SPI1->CR1 = 0;

    SPI1->CR1 |= (1u<<2);
    SPI1->CR1 |= (0u<<1);
    SPI1->CR1 |= (0u<<0);
    SPI1->CR1 |= (3u<<3);
    SPI1->CR1 |= (1u<<9);
    SPI1->CR1 |= (1u<<8);
    SPI1->CR1 |= (1u<<6);
}

void spi1_write(uint8_t data){
    while(!(SPI1->SR & (1u<<1))){}
    SPI1->DR = data;
    while(SPI1->SR & (1u<<7)){}
}