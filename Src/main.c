#include <stdio.h>
#include "uart.h"
#include "gpio.h"
#include "tim.h"
#include "systick.h"
#include "spi.h"

int main(void){
    gpio_init();
    uart_init();
    tim2_init();
    spi_init();
    display_init();
    
    uint8_t data[5];
    while(1){
        dht11_send_start_signal();
        uint8_t status = dht11_wait_for_response();
        if(status != 0 ){
            printf("error: %d\n", status);
            delay_ms(2000);
            continue;
        }
        
        uint8_t result = dht11_read_data(data);

        if(result == 0){
            printf("Humidity: %d.%d %%  Temp: %d.%d C\r\n",
                data[0], data[1], data[2], data[3]);
        }
        else{
            printf("Data error: %d\n", result);
        }

        delay_ms(1500);
        
    }
}