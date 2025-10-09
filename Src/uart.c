#include "uart.h"

#define GPIOAEN     (1U<<0)
#define UART2EN     (1U<<17)

#define DBG_UART_BAUDRATE   115200
#define SYS_FREQ    16000000
#define APB1_CLK    SYS_FREQ
#define CR1_TE      (1U<<3)
#define CR1_UE      (1U<<13)
#define SR_TXE      (1U<<7)

static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);
static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate);
static void uart_write(int ch);


void uart_init(void){
    RCC->AHB1ENR |= GPIOAEN;
    
    GPIOA->MODER |= (1U<<5);
    GPIOA->MODER &= ~(1U<<4);

    GPIOA->AFR[0] &= ~(1U<<11);
    GPIOA->AFR[0] |= (1U<<10);
    GPIOA->AFR[0] |= (1U<<9);
    GPIOA->AFR[0] |= (1U<<8);

    RCC->APB1ENR |= UART2EN;

    uart_set_baudrate(SYS_FREQ, DBG_UART_BAUDRATE);

    USART2->CR1 |= CR1_TE;
    USART2->CR1 |= CR1_UE;

}

static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate){
    return ((periph_clk + (baudrate/2U))/baudrate);
}

static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate){
    USART2->BRR = compute_uart_bd(periph_clk, baudrate);
}

static void uart_write(int ch){
    while(!(USART2->SR & SR_TXE)){}

    USART2->DR = (ch & 0xFF);
}

int __io_putchar(int ch){
    uart_write(ch);
    return ch;
}