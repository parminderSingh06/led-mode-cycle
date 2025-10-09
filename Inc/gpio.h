#ifndef GPIO_H_
#define GPIO_H_


#include <stdint.h>
#include "stm32f4xx.h"

void gpio_init(void);
void dht11_send_start_signal(void);
uint8_t dht11_wait_for_response(void);
uint8_t dht11_read_data(uint8_t *data);

#endif