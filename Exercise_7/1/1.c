#include <mega16.h>
#include <stdlib.h>
#include <stdio.h>
#include <delay.h>
#include <alcd.h>

  int id,p,i,s=23,m=41,h=18,motor=130;
unsigned char key ;
unsigned char x[4],y[4],h1[1],w1[1],wa[10],mo[5],temp[5];

unsigned char key_pad(void)  
{
PORTC.4=0;PORTC.5=1;PORTC.6=1;PORTC.7=1;   
if(!PINC.0) return 'K';if(!PINC.1) return '9';
if(!PINC.2) return '8';if(!PINC.3) return '7';
PORTC.4=1;PORTC.5=0;PORTC.6=1;PORTC.7=1;   
if(!PINC.0) return 'K';if(!PINC.1) return '6';
if(!PINC.2) return '5';if(!PINC.3) return '4';
PORTC.4=1;PORTC.5=1;PORTC.6=0;PORTC.7=1;   
if(!PINC.0) return 'K';if(!PINC.1) return '3';
if(!PINC.2) return '2';if(!PINC.3) return '1';
PORTD.4=1;PORTC.5=1;PORTC.6=1;PORTC.7=0;   
if(!PINC.0) return 'K';if(!PINC.1) return '=';
if(!PINC.2) return '0';if(!PINC.3) return 'E';
return 'N';
}


void main(void)
{                              

DDRC=0xF0;
PORTC=0x0F;

DDRB=0x03;
PORTB=0x00;
PINB.2=1;
PINB.3=1;
PINB.4=1;

UCSRA=0x00;
UCSRB=0x18;
UCSRC=0x86;
UBRRH=0x00;
UBRRL=0x33;
 
lcd_init(16);
while (1)
{          
           lcd_gotoxy(5,0);
           lcd_puts("ID:");
           lcd_gotoxy(5,1);
           lcd_puts("PW:");
            key=key_pad(); 
            delay_ms(230);

                    while(key!='K'||(mo[4]=='0'))           
           {   

           while(key!='N')           
           {  
            
               x[i]=key;
               id=atoi(x);
               i++;     
              key='N'; 
             }  
             

           lcd_gotoxy(10,0);
           sprintf(h1,"%d",id); 
           lcd_puts(h1); 
            key=key_pad(); 
            delay_ms(230);
           if(key=='=') 
             {
            key='K';
              
            i=0;    
              } 

          }                           
          
          
           key='N';
           
                     while(key!='K'||(mo[4]=='0'))           
           {   
           while(key!='N')           
           {  
            
               y[i]=key;
             p=atoi(y);
              i++;     
              key='N'; 
             }   
                                   

           lcd_gotoxy(10,1);
           sprintf(w1,"%d",p); 
           lcd_puts(w1);
           key=key_pad();
           delay_ms(230);
           if(key=='=') 
             {
            key='K'; 

           i=0;    
              
               }
          }                               
           
          while((id==1)&&(p==3)||(mo[4]=='0'))
          { 
          
           PORTB=0x01;
           s++;
           
           if(s==59)
           {
           m++;s=0;

           if(m==59)
           {h++;m=0;}

           if(h==23)
           {h=0;m=0;s=0;}
           }
           if(PINB.2==0)
           m++;
           if(PINB.3==0)
           h++;
           if(PINB.4==0)
           motor++;           
           lcd_clear();
           
           lcd_gotoxy(10,0);
           lcd_puts(temp);  
                    
           lcd_gotoxy(0,0);
           sprintf(wa,"%d:%d:%d",h,m,s); 
           lcd_puts(wa);  

           lcd_gotoxy(0,1);
           sprintf(mo,"rpm:%d",motor);          
           lcd_puts(mo);  

           delay_ms(1000);
           id=1;
           p=3;
          }

          while((id!=1)&&(p!=3)||(mo[4]=='0'))
          { 

           PORTB=0x02; 
           lcd_gotoxy(0,0);
           lcd_puts("error");
           }
}
}