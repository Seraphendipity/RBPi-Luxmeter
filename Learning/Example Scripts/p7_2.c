/* p7_2.c ADC14 conversion of internal temperature sensor
 *
 * In this example, conversion result memory register 3 is used.
 * The internal temperature sensor in the REF_A module is used.
 * It requires that the REF_A module is powered up and the
 * temperature sensor is enabled.
 * The sensor is connected to channel 22 and mapped by bit 23
 * of ADC14->CTL1 register. Conversion is started by software trigger.
 * The bits 3-0 of the 10 bit conversion result are displayed on
 * the tri-color LEDs.
 *
 * Heat the MSP432 MCU with a hot air blower and see the LED color change.
 *
 * Tested with Keil 5.20 and MSP432 Device Family Pack V2.2.0
 * on XMS432P401R Rev C.
 */

#include "msp.h"

int main(void) {
    int result;

    /* Configure P2.2-P2.0 as output */
    P2->SEL0 &= ~7;
    P2->SEL1 &= ~7;
    P2->DIR |= 7;

    REF_A->CTL0 |= 1;   /* power up REF for temperature sensor */
    REF_A->CTL0 &= ~8;  /* enable temperature sensor */

    ADC14->CTL0 =  0x00000010;    /* power on and disabled during configuration */
    ADC14->CTL0 |= 0x04883000;    /* S/H pulse mode, use int. temp, sysclk, 32 sample clocks, software trigger */
    ADC14->CTL1 =  0x00000010;    /* 10-bit resolution */
    ADC14->CTL1 |= 0x00800000;    /* select internal temperature sensor */
    ADC14->MCTL[3] |= 22;         /* internal temp sensor */
    ADC14->CTL1 |=  0x00030000;   /* start at mem reg 3 */
    ADC14->CTL0 |=  0x00000002;   /* enable ADC */

    while (1) {
        ADC14->CTL0 |= 1;         /* start a conversion */
        while (!ADC14->IFGR0);    /* wait till conversion complete */
        result = ADC14->MEM[3];   /* read conversion result */
        P2->OUT = result;         /* dump it at the LEDs */
    }
}
