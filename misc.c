#include "stm8s.h"
#include "misc.h"
extern struct BitFlag SysFlag;

void SystemInit(void)
{
    CLK->CKDIVR = CLK_CKDIVR_RESET_VALUE; // Set the frequency to 2 MHz

	GPIOE->DDR = 0x20;
	GPIOE->CR1 = 0x20;

    /*
       Configure timer
       fmaster = 2 MHz,
       Tim4 clk time = 1/(2M/(2^7)) =1/15.625KHz=64uS
       one interrupt time is 64us * 157 = 10.048mS
    */
    TIM4->CR1 = TIM4_CR1_CEN;
    TIM4->PSCR = 0x07;
    TIM4->EGR = 0x01;
    TIM4->ARR = 157;
    TIM4->IER = 0x01;

}

void UartInit(void)
{
    /*
       UART2 Baud rate =9600,
       BR register = 2M / 9600 = 208.3 = 0xD1

    */
    UART2->SR &=0xBF;
    UART2->BRR1 =0x0D;UART2->BRR2=0x01;
    UART2->CR1 = 0x00;
    UART2->CR2 = UART2_CR2_RIEN | UART2_CR2_TEN|UART2_CR2_REN;
    UART2->CR3 = 0x00;
}

void putchar(char c)
{
    while(((UART2->SR)&0x80) != 0x80);
    UART2->DR=c;
}
