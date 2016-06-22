#ifndef _MISC_H
#define _MISC_H


void SystemInit(void);
void UartInit(void);
void putchar(char);

struct BitFlag{
        unsigned x1     :1;  // UART received OK
        unsigned RXDone :1;
        unsigned x2     :1;  // Go to boot loader
        unsigned x3     :1;  //
        unsigned x4     :1;
        unsigned x5     :1;
        unsigned x6     :1;
        unsigned x7     :1;
        };

#endif // misc_H
