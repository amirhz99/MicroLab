#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>



int LEVEL = 0;
char LL[] = {0b0101, 0b0110, 0b1010, 0b1001};
float iter = 0;

void NLL()
{
    if (++LEVEL >= 4)
    {
        LEVEL = 0;
    }
    PORTA = LL[LEVEL];
}

ISR(TIMER0_OVF_vect)
{
    iter += 0.5;

    if (iter >= 19.5f)
    {
        iter = 0;
    }
}

ISR(TIMER0_COMP_vect)
{
    iter += 0.5;

    if (iter >= 19.5f)
    {
        iter = 0;
        NLL();
    }
}

int main()
{
    DDRC = 0;
    while ((PINC & 0x04) == 0x04);
    DDRA = 0xFF;
    PORTA = 0x00;

    TCCR0 = (0 << COM01) | (1 << COM00) | (1 << CS00);
    TIMSK = (1 << TOIE0) | (1 << OCIE0);
    TCNT0 = 0x00;
    OCR0 = 128;

    sei();

    while (true)
    {
    }
}