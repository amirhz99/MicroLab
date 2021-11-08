Connect the switch to the micro C2 pin (connect the resistor so that when the switch is pressed, the C2 port is zero.
Be). Then connect the L293 driver to the stepper motor to ports A0 to A3 (wing shape).
Write a program that, when the key is triggered, uses the stepper motor motion table, the motor motion signals
On port A0 to A3 so that after placing each control signal in the port, the program 5ms
Stop the engine from moving and then send the next motion signal in the next 5ms. Program
Write the motor motion in the zero timer interrupt response function. Your entire answer (Proteus file and compiler program
Hex and program c (put in part1 folder