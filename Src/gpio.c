#include "gpio.h"
#include "systick.h"
#include "tim.h"

void gpio_init(void){
    RCC->AHB1ENR |= (1u<<2);

    GPIOC->ODR |= (1u<<8);

    GPIOC->MODER &= ~(3u<<16);
    GPIOC->MODER |= (1u<<16);
}

void dht11_send_start_signal(void){
    GPIOC->ODR &= ~(1u<<8);
    delay_ms(18);
    GPIOC->ODR |= (1u<<8);
    delay_us(30);
    gpio_switch2_input_mode();
}

uint8_t dht11_wait_for_response(void){
    TIM2->CNT = 0;
    while(GPIOC->IDR & (1u<<8)){
        if(TIM2->CNT > 200) return 1;
    }

    TIM2->CNT = 0;
    while(!(GPIOC->IDR & (1u<<8))){
        if(TIM2->CNT > 200) return 2;
    }

    uint32_t low_time = TIM2->CNT;

    TIM2->CNT = 0;
    while(GPIOC->IDR & (1u<<8)){
        if(TIM2->CNT > 200) return 3;
    }

    uint32_t high_time = TIM2->CNT;

    return 0;
}

static void gpio_switch2_input_mode(void){
    GPIOC->MODER &= ~(3u<<16);   
}

static uint8_t dht11_read_data_bit(void){

    TIM2->CNT = 0;
    while (!(GPIOC->IDR & (1U << 8))) {
        if (TIM2->CNT > 200) return 4;
    }
    
    TIM2->CNT = 0;
    while(GPIOC->IDR & (1u<<8)){
        if(TIM2->CNT > 200) return 5;
    }

    uint32_t pulse_length = TIM2->CNT;
    
    if(pulse_length > 50){
        return 1;
    }
    else{
        return 0;
    }
}

static uint8_t dht11_read_byte(void){
    uint8_t byte_value = 0;

    for(uint32_t i=0; i<8; i++){
        uint8_t bit = dht11_read_data_bit();

        if(bit != 1 && bit != 0){
            return 6;
        }

        byte_value = (byte_value << 1) | bit;
    }

    return byte_value;
}

uint8_t dht11_read_data(uint8_t *data){
    for(int i=0; i<5; i++){
        data[i] = dht11_read_byte();
        if(data[i] == 6) return 7; 
    }

    uint8_t checksum = data[0] + data[1] + data[2] + data[3];
    checksum &= 0xFF;

    if(checksum == data[4]){
        return 0;
    }
    else{
        return 8;
    }
}