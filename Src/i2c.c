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
    
}