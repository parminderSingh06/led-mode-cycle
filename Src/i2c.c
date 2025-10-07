#include "i2c.h"

#define GPIOBEN     (1U<<1)
#define I2C1EN      (1U<<21)
#define I2C_100KHZ  80
#define SD_MODE_MAX_RISE_TIME   17
#define CR1_PE      (1U<<0)
#define SR2_BUSY    (1U<<1)
#define CR1_START   (1U<<8)
#define SR1_SB      (1U<<0)
#define SR1_ADDR    (1U<<1)
#define SR1_TXE     (1U<<7)
#define CR1_ACK     (1U<<10)
#define CR1_STOP    (1U<<9)
#define SR1_RXNE    (1U<<6)
#define SR1_BTF     (1U<<2)

//PB8 ---- SCL
//PB9 ----- SDA

void i2c_init(void){
    RCC->AHB1ENR |= GPIOBEN;

    GPIOB->MODER &= ~(1U<<16);
    GPIOB->MODER |= (1U<<17);

    GPIOB->MODER &= ~(1U<<18);
    GPIOB->MODER |= (1U<<19);

    GPIOB->OTYPER |=(1U<<8);
    GPIOB->OTYPER |=(1U<<9);

    GPIOB->PUPDR &=~(1U<<19);
    GPIOB->PUPDR |=(1U<<18); 
    
    GPIOB->PUPDR &=~(1U<<17);
    GPIOB->PUPDR |=(1U<<16);

    GPIOB->AFR[1] &=~(1U<<0);
    GPIOB->AFR[1] &=~(1U<<1);
    GPIOB->AFR[1] |=(1U<<2);
    GPIOB->AFR[1] &=~(1U<<3);

    GPIOB->AFR[1] &=~(1U<<4);
    GPIOB->AFR[1] &=~(1U<<5);
    GPIOB->AFR[1] |=(1U<<6);
    GPIOB->AFR[1] &=~(1U<<7);    

    RCC->APB1ENR |= I2C1EN;

    I2C1->CR1 |= (1U<<15);

    I2C1->CR1 &= ~(1U<<15);

    I2C1->CR2 |= (1U<<4);

    I2C1->CCR = I2C_100KHZ;

    I2C1->TRISE = SD_MODE_MAX_RISE_TIME;

    I2C1->CR1 |= (1U<<0);
}