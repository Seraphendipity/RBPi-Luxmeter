/* p7_4.c ADC14 conversion of external temperature sensor
 *
 * In this example, conversion result memory register 2 is used.
 * Input channel A1 using P5.4 is connected to an external temperature
 * sensor. Assuming we use LM34 or LM35, which produces 10mV per degree,
 * the conversion result is scaled to degree and displayed through
 * UART0 and a terminal emulator (putty, tera term) on the PC.
 *
 * Tested with Keil 5.20 and MSP432 Device Family Pack V2.2.0
 * on XMS432P401R Rev C.
 */

#include "msp.h"
#include <stdio.h>

void UART0_init(void);
void UART0_putchar(char c);
void UART0_puts(char* s);

void delayMs(int n);

int main(void) {
    int result;
    char buffer[20];

    UART0_init();
    
    ADC14->CTL0 =  0x00000010;    /* power on and disabled during configuration */
    ADC14->CTL0 |= 0x04080300;    /* S/H pulse mode, sysclk, 32 sample clocks, software trigger */
    ADC14->CTL1 =  0x00000030;    /* 14-bit resolution */
    ADC14->MCTL[2] = 1;           /* A1 input, single-ended, Vref=AVCC */
    P5->SEL1 |= 0x10;             /* Configure P5.4 for A1 */
    P5->SEL0 |= 0x10;
    ADC14->CTL1 |= 0x00020000;    /* convert for mem reg 2 */
    ADC14->CTL0 |= 2;             /* enable ADC after configuration*/

    while (1) {
        ADC14->CTL0 |= 1;         /* start a conversion */
        while (!ADC14->IFGR0);    /* wait till conversion complete */
        result = ADC14->MEM[2];   /* read conversion result */
        result = result * 330 / 16384; /* scale to degree for display */
        sprintf(buffer, "%d\r\n", result);  /* convert it to char string */
        UART0_puts(buffer);     /* send it out through UART0 */
        
        delayMs(10);			/* you can change or remove the delay */
    }
}

void UART0_init(void) {
    EUSCI_A0->CTLW0 |= 1;     /* put in reset mode for config */
    EUSCI_A0->MCTLW = 0;      /* disable oversampling */
    EUSCI_A0->CTLW0 = 0x0081; /* 1 stop bit, no parity, SMCLK, 8-bit data */
    EUSCI_A0->BRW = 26;       /* 3000000 / 115200 = 26 */
    P1->SEL0 |= 0x0C;         /* P1.3, P1.2 for UART */
    P1->SEL1 &= ~0x0C;
    EUSCI_A0->CTLW0 &= ~1;    /* take UART out of reset mode */
}

void UART0_putchar(char c) {
    while(!(EUSCI_A0->IFG&0x02)) { }  /* wait for transmit buffer empty */
    EUSCI_A0->TXBUF = c;             /* send a char */
}

void UART0_puts(char* s) {
    while (*s != 0)     /* if not end of string */
    UART0_putchar(*s++);      /* send the character through UART0 */
}

/* delay milliseconds when system clock is at 3 MHz */
void delayMs(int n) {
    int i, j;
    
    for (j = 0; j < n; j++)
        for (i = 750; i > 0; i--);      /* Delay 1 ms */
}
