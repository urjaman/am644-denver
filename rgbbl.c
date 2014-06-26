#include "main.h"
#include <avr/io.h>
#include "rgbbl.h"


void rgbbl_set(uint8_t r, uint8_t g, uint8_t b)
{
    OCR0A = r;
    OCR0B = g;
    DDRB |= _BV(3); // OC0A, red
    DDRB |= _BV(4); // OC0B, green
}

void rgbbl_init(void) {
    TCCR0A = 0xF3; /* Inverting mode on both OCR0A and OCR0B, Fast PWM mode. */
    TCCR0B = 0x01; /* Go (No division). */
    OCR0A = 0;
    OCR0B = 0;
    DDRB |= _BV(3); // OC0A, red
    DDRB |= _BV(4); // OC0B, green
}

void rgbbl_off(void)
{
    rgbbl_set(0,0,0);
    DDRB &= ~_BV(3);
    DDRB &= ~_BV(4);
}
