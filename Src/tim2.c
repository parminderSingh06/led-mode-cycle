#include "tim.h"

void tim2_init(void){
    RCC->APB1ENR |= (1u<<0);
    TIM2->CR1 = 0;
    TIM2->PSC = (SystemCoreClock / 1000000) - 1;
    TIM2->ARR = 0xFFFFFFFF;
    TIM2->EGR |= (1U << 0);   
    TIM2->CR1 |= (1u<<0);
}