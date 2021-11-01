#include <avr/io.h>
#include <avr/delay.h>


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

void LStr(char *str)
{
    for (int i = 0; str[i] != 0; i++)
        LChar(str[i]);
}


int main()
{

    DDRA = 0xFF;
    DDRB = 0xFF;

    _delay_ms(20);

    LCDCMD(0x38);
    LCDCMD(0x0C);
    LCDCMD(0x06);
    LCDCMD(0x01);
    LCDCMD(0x80);

    LStr("Hello World");

    while (true){}

    return 0;
}
