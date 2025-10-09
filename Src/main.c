#include <stdio.h>
#include "uart.h"
#include "gpio.h"

int main(void){
    gpio_init();
    uart_init();

    while(1){
        dht11_send_start_signal();
    }
}