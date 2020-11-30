/* www.MicroDigitalEd.com
 * p7_3.c Multiple analog input conversions in a sequence
 *
 * This program is an example of performing a sequence of
 * multiple channel conversion. The sequence starts at result
 * memory register 4 and ends at result memory register 6.
 * The assignments of input channels are as follows:
 * MEM4 - A8  - P4.5
 * MEM5 - A6  - P4.7
 * MEM6 - A10 - P4.3
 *
 * Once the conversions are started by software, the program
 * polls for the completion flag of MEM6, the last channel.
 * When the last channel conversion is completed, the conversion
 * results are read and displayed using UART0.
 * Using a terminal emulator (putty, tera term) set at 115200 Baud,
 * you should be able to see the conversion results on the terminal.
 *
 * Tested with Keil 5.20 and MSP432 Device Family Pack V2.2.0
 * on XMS432P401R Rev C.
 */

#include "msp.h"
#include "stdio.h"

void UART0_init(void);
void UART0_putchar(char c);
void UART0_puts(char* s);

void delayMs(int n);

int main(void) {
    char buffer[80];
    int data[3] = {0};

    ADC14->CTL0 =  0x00000010;    /* power on and disabled during configuration */
    ADC14->CTL0 |= 0x040A0380;    /* S/H pulse mode, sysclk, 32 sample clocks, multiple channel conversion sequence, software trigger */
    ADC14->CTL1 =  0x00040020;    /* 12-bit resolution, starting from result memory 4 */

    ADC14->MCTL[4] |= 8;            /* select A8 input; Vref=AVCC */
    P4->SEL1 |= 0x20;             /* Configure P4.5 for A8 */
    P4->SEL0 |= 0x20;

    ADC14->MCTL[5] |= 6;            /* select A6 input; Vref=AVCC */
    P4->SEL1 |= 0x80;             /* Configure P4.7 for A6 */
    P4->SEL0 |= 0x80;

    ADC14->MCTL[6] |= 10 | 0x80;    /* select A10 input; Vref=AVCC; end of sequence */
    P4->SEL1 |= 0x08;             /* Configure P4.3 for A10 */
    P4->SEL0 |= 0x08;

    ADC14->CTL0 |=  0x00000002;   /* enable the converter */
    UART0_init();

    while (1) {
        ADC14->CTL0 |= 1;         /* start a conversion sequence */
        while (!(ADC14->IFGR0 & 0x00000040)); /* wait till last channel in the sequence complete */
        data[0] = ADC14->MEM[4];    /* read the conversion results */
        data[1] = ADC14->MEM[5];
        data[2] = ADC14->MEM[6];
        /* convert to an ASCII string for UART0 output */
        sprintf(buffer, "\r\nA8: %d, A6: %d, A10:%d", data[0], data[1], data[2]);
        UART0_puts(buffer);
			
        delayMs(10); /* you can change or remove the delay time */
    }
}

/* UART0 is connected to virtual COM port through the USB debug connection */
void UART0_init(void) {
    EUSCI_A0->CTLW0 |= 1;             /* put in reset mode for config */
    EUSCI_A0->MCTLW = 0;              /* disable oversampling */
    EUSCI_A0->CTLW0 = 0x0081;         /* 1 stop bit, no parity, SMCLK, 8-bit data */
    EUSCI_A0->BRW = 26;               /* 3000000 / 115200 = 26 */
    P1->SEL0 |= 0x0C;                 /* P1.3, P1.2 for UART */
    P1->SEL1 &= ~0x0C;
    EUSCI_A0->CTLW0 &= ~1;            /* take UART out of reset mode */
}

void UART0_putchar(char c) {
    while(!(EUSCI_A0->IFG&0x02)) { }  /* wait for transmit buffer empty */
    EUSCI_A0->TXBUF = c;              /* send a char */
}

void UART0_puts(char* s) {
    while (*s != 0)             /* if not end of string */
    UART0_putchar(*s++);        /* send the character through UART0 */
}

/* delay milliseconds when system clock is at 3 MHz */
void delayMs(int n) {
    int i, j;
    
    for (j = 0; j < n; j++)
        for (i = 750; i > 0; i--);      /* Delay 1 ms */
}
