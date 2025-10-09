#include "gpio.h"

void gpio_init(void){
    RCC->AHB1ENR |= (1u<<0);

    GPIOC->ODR |= (1u<<8);

    GPIOC->MODER &= ~(1u<<17);
    GPIOC->MODER |= (1u<<16);
}