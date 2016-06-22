
#include <stdint.h>
#include <stdio.h>
#include "STM8S.h"
#include "misc.h"

struct BitFlag SysFlag;
unsigned char time10ms,RXTimer;
unsigned char RXIndex;
unsigned char RXBuf[20];

void UART2Recive(void) __interrupt 21
{
    RXBuf[RXIndex++] = UART2->DR;
    RXTimer=0;
    __asm__("bres 0x5240,#5\n"); //clear UART2->SR->RXNE
}
void Tim4Int(void) __interrupt 23
{
    TIM4->SR1=0;
    time10ms++;
    if(RXIndex>0){RXTimer++;}
}

void main(void)
{

    SystemInit();
    UartInit();


    SysFlag.RXDone = 0;
    RXIndex=0;
    time10ms=0;
    RXTimer=0;
    GPIOE->ODR&=~(0x20);

    enableInterrupts();

	while(1)
    {
        if(time10ms>50)
        {
            __asm__("bcpl 0x5014,#5\n");//GPIOE->ODR = GPIOE->ODR ^ 0x20;
            time10ms=time10ms-50;
        }
        if(RXTimer>10)
        {
            unsigned char i;
            printf("%d",RXIndex);
            for(i=0;i<RXIndex;i++)
            {
                putchar(RXBuf[i]);
            }
            RXIndex=0;
            RXTimer=0;
            SysFlag.RXDone=1;
        }
        if(SysFlag.RXDone)
        {
            SysFlag.RXDone=0;
        }
    }
}
