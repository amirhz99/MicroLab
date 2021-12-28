
#include <mega16.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>     
#include <stdlib.h>     

#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))  

unsigned char step[8]={0x01,0x03,0x02,0x06,0x04,0x0C,0x08,0x09};
int i,z;

unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
delay_us(10);
ADCSRA|=(1<<ADSC);
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}
void main(void)
{
int     a=0 ;              
float   Temperature ;     
char    Buffer_LCD[5],in[8]; 

UCSRA=0x00;
UCSRB=0x18;
UCSRC=0x86;
UBRRH=0x00;
UBRRL=0x33;
 
DDRC=0xFF;
PORTC=0x00; 

DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);
 
DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

ADMUX=ADC_VREF_TYPE;      
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (1<<ADPS1) | (0<<ADPS0);
SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

lcd_init(16);    
lcd_clear();    

while (1)
      { 
      a=read_adc(0);            
      Temperature=(a/2.054) ;                           
      sprintf(Buffer_LCD,"T=%3.0f",Temperature);    
      lcd_gotoxy(0,1);    
      lcd_puts(Buffer_LCD);
      Buffer_LCD[4]='0';
      puts(Buffer_LCD);
      gets(in,4);  
      lcd_gotoxy(7,1);     
      lcd_putsf("C");         
      delay_ms(500);
      itoa(z,in);
      Buffer_LCD[4]='0';
               
      for(i=0;i<=7;i++)        
          {
           PORTC=step[i];       
           delay_ms(z); 
           }    
      }
}
