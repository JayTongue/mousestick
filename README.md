# Mousestick

Justin Tung, 2025

------------------------------------------

This is a simple arduino code for using a common 5-pin joystick as a mouse with a RP2040 microcontroller. The joystick I used is a HW-504, but I believe this code can be modified to work with others as well. 

One important thing to pay attention to is whether your joystick takes 3.3v or 5v as input. 

The pin assignment can changed, but keep in mind that the pin on the microcontroller needs to be capable of analog input. 

As currently implemented, a single click is a left click, and a double click is a right click.
