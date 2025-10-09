#include "systick.h"

#define CTRL_EN (1U<<0)
#define CTRL_SRC (1U<<2)
#define CTRL_FLG (1U<<16)

#define CLOCK_CYCLES_MS 16000
#define CLOCK_CYCLES_US 16

void delay_ms(uint32_t ms){
    SysTick->LOAD = CLOCK_CYCLES_MS-1;

    SysTick->VAL = 0;

    SysTick->CTRL |= CTRL_EN;

    SysTick->CTRL |= CTRL_SRC;

    for(uint32_t i=0;i< ms;i++){
       while(!(SysTick->CTRL & CTRL_FLG)){} 
    }

    SysTick->CTRL = 0;
}

void delay_us(uint32_t us){
    SysTick->LOAD = CLOCK_CYCLES_US-1;

    SysTick->VAL = 0;

    SysTick->CTRL |= CTRL_EN;

    SysTick->CTRL |= CTRL_SRC;

    for(uint32_t i=0;i <us; i++){
       while(!(SysTick->CTRL & CTRL_FLG)){} 
    }

    SysTick->CTRL = 0;
}