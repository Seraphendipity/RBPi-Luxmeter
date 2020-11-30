/* p7_1.c ADC14 software trigger conversion
 *
 * In this example, conversion result memory register 5 is used.
 * Analog input channel 6 using pin P4.7 is configure for result
 * memory register 5. Conversion is started by software trigger.
 * The bits 10-8 of the 12 bit conversion result are displayed on
 * the tri-color LEDs.
 *
 * Connect a potentiometer to P4.7 and see the color changes when
 * the potentiometer is turned.
 *
 * Tested with Keil 5.20 and MSP432 Device Family Pack V2.2.0
 * on XMS432P401R Rev C.
 */

#include "msp.h"

int main(void) {
    int result;

    /* Configure P2.2-P2.0 as output for tri-color LEDs */
    P2->SEL0 &= ~7;
    P2->SEL1 &= ~7;
    P2->DIR |= 7;

    ADC14->CTL0 =  0x00000010;    /* power on and disabled during configuration */
    ADC14->CTL0 |= 0x04080300;    /* S/H pulse mode, sysclk, 32 sample clocks, software trigger */
    ADC14->CTL1 =  0x00000020;    /* 12-bit resolution */
    ADC14->MCTL[5] = 6;           /* A6 input, single-ended, Vref=AVCC */
    P4->SEL1 |= 0x80;             /* Configure P4.7 for A6 */
    P4->SEL0 |= 0x80;
    ADC14->CTL1 |= 0x00050000;    /* convert for mem reg 5 */
    ADC14->CTL0 |= 2;             /* enable ADC after configuration*/

    while (1) {
        ADC14->CTL0 |= 1;         /* start a conversion */
        while (!ADC14->IFGR0);    /* wait till conversion complete */
        result = ADC14->MEM[5];   /* read conversion result */
        P2->OUT = result >> 8;    /* display bits 10-8 on tri-color LEDs */
    }
}
