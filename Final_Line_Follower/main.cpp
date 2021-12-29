#define FCPU 1000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

int counter_R_move = 0,counter_L_move = 0,step_R_move = 0,step_L_move = 0,R_move_speed = 0,L_move_speed = 0;
bool R_move = false,L_move = false;

// set the overflow cunter
float counter_speed_manager[] = {(FCPU / float(256)) * 0.1f, (FCPU / float(256)) * 0.2f};


void timer0()
{
    sei();
    TCCR0 = (1 << CS00);
    TIMSK = (1 << TOIE0);
    TCNT0 = 0x00;
}

// T1, T2, T3 , T4 steper level
unsigned char stepper_motor[] = {0b0101, 0b0110, 0b1010, 0b1001};

ISR(TIMER0_OVF_vect)
{
    if (++counter_R_move >= counter_speed_manager[R_move_speed])
    {
        counter_R_move = 0;
        if (R_move)
            if (++step_R_move >= 4)
                {
                    step_R_move = 0;
                }
                PORTD = stepper_motor[step_R_move];
                }
    if (++counter_L_move >= counter_speed_manager[L_move_speed])
    {
        counter_L_move = 0;
        if (L_move)
            if (++step_L_move >= 4)
            {
                step_L_move = 0;
            }
            PORTC = stepper_motor[step_L_move];
            }
}

int main()
{
    DDRA = 0x00;
    DDRC = 0xFF;
    DDRD = 0xFF;
    PORTC = 0x00;
    PORTD = 0x00;

    timer0();

    while (true) {
        char CompareInput = (PINA & 0b00011111);
        if (CompareInput == 0b00000100) {
            R_move=true;
            L_move=true;
            R_move_speed = 0;
            L_move_speed = 0;
        }
        else if (CompareInput == 0b00001110) {
            R_move=true;
            L_move=true;
            R_move_speed = 1;
            L_move_speed = 1;
        }
        else if (CompareInput == 0b00000011) {
            R_move=false;
            L_move=true;
            L_move_speed = 1;
        }
        else if (CompareInput == 0b00000001) {
            R_move=false;
            L_move=true;
            L_move_speed = 0;
        }
        else if (CompareInput == 0b00000110) {
            R_move=true;
            L_move=true;
            R_move_speed = 1;
            L_move_speed = 0;
        }
        else if (CompareInput == 0b00000010) {
            R_move=true;
            L_move=true;
            R_move_speed = 1;
            L_move_speed = 0;
        }
        else if (CompareInput == 0b00001100) {
            R_move=true;
            L_move=true;
            R_move_speed = 0;
            L_move_speed = 1;
        }
        else if (CompareInput == 0b00001000) {
            R_move=true;
            L_move=true;
            R_move_speed = 0;
            L_move_speed = 1;
        }
        else if (CompareInput == 0b00011000) {
            R_move=true;
            L_move=false;
            R_move_speed = 1;
        }
        else if (CompareInput == 0b00010000) {
            R_move=true;
            L_move=false;
            R_move_speed = 0;
        }
        else {
            R_move=false;
            L_move=false;
        }
    }
}