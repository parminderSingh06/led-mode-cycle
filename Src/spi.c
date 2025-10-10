#include "spi.h"
#include "systick.h"

#define CS_LOW()   (GPIOA->ODR &= ~(1u << 4))
#define CS_HIGH()  (GPIOA->ODR |=  (1u << 4))
#define DC_LOW()   (GPIOA->ODR &= ~(1u << 3))
#define DC_HIGH()  (GPIOA->ODR |=  (1u << 3))
#define RST_LOW()  (GPIOA->ODR &= ~(1u << 2))
#define RST_HIGH() (GPIOA->ODR |=  (1u << 2))


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

static void spi1_write(uint8_t data){
    while(!(SPI1->SR & (1u<<1))){}
    SPI1->DR = data;
    while(SPI1->SR & (1u<<7)){}
}

static void display_write_command(uint8_t cmd){
    CS_LOW();
    DC_LOW();
    spi1_write(cmd);
    CS_HIGH();
}

static void display_write_data(uint8_t data){
    CS_LOW();
    DC_HIGH();
    spi1_write(data);
    CS_HIGH();
}

static void display_reset(void){
    RST_LOW();
    delay_ms(20);
    RST_HIGH();
    delay_ms(120);
}

void display_init(void){
    display_reset();

    display_write_command(0x11);
    delay_ms(120);

    display_write_command(0x36);
    display_write_data(0x55);

    display_write_command(0x29);
    delay_ms(20);
}