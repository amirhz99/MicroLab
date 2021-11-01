#include <stdio.h>
#include <avr/io.h>
#include <avr/delay.h>
#include <util/atomic.h>

void LChar(unsigned char char_data)
{
    PORTC = char_data;
    PORTA |= (1 << PC0);
    PORTA &= ~(1 << PC1);
    PORTA |= (1 << PC2);
    _delay_us(1);
    PORTA &= ~(1 << PC2);
    _delay_ms(1);
}

void LCDCMD(unsigned char cmnd)
{
    PORTC = cmnd;
    PORTA &= ~(1 << PC0);
    PORTA &= ~(1 << PC1);
    PORTA |= (1 << PC2);
    _delay_us(1);
    PORTA &= ~(1 << PC2);
    _delay_ms(3);
}

void LStr(char *str)
{
    for (int i = 0; str[i] != 0; i++)
        LChar(str[i]);
}

int t = 0;
unsigned int counter = 0;

ISR(TIMER2_OVF_vect)
{
    counter++;

    if (counter == 61)
    {
        counter = 0;
        return;
    }

    if (counter == 9)
    {
        t++;
        short hour = t / 3600;
        short minute = (t % 3600) / 60;
        short second = (t % 3600) % 60;
        LCDCMD(0x01);
        char buffer[20];
        sprintf(buffer, "%02d:%02d:%02d", hour, minute, second);
        LStr(buffer);
    }
}

int main()
{
    DDRA = 0xFF;
    DDRB = 0xFF;

    _delay_ms(35);

    LCDCMD(0x38);
    LCDCMD(0x0C);
    LCDCMD(0x06);
    LCDCMD(0x01);
    LCDCMD(0x80);

    TIMSK = 1 << TOIE2;
    TCCR2 = 1 << CS22;

    sei();

    while (true){}

    return 0;
}