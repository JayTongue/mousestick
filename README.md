# Mousestick

Justin Tung, 2025

------------------------------------------

<img src="https://github.com/JayTongue/mousestick/blob/main/exhibits/IMG_4530.jpeg" width="500" /> <img src="https://github.com/JayTongue/mousestick/blob/main/exhibits/IMG_4532.jpeg" width="500" />


This is a simple arduino code for using a common 5-pin joystick as a mouse with a RP2040 microcontroller. The joystick I used is a HW-504, but I believe this code can be modified to work with others as well. 

One important thing to pay attention to is whether your joystick takes 3.3v or 5v as input. 

The pin assignment can changed, but keep in mind that the pin on the microcontroller needs to be capable of analog input. 

As currently implemented, single click is a left click, double click is a right click, and triple click stickies on left click to mimic click and drag. 

Since the milis() function is stored into an unsigned long, this mouse will have a behavior where every 50 days or so, the number of miliseconds will overflow the alloted data space and reset back to 0. I'm fine with this since you'd have to try to double or triple click in a tiny window exactly over that time period, or make clicks exactly 50ish days apart to catch the window the next time it comes around. Since neither of these are really likely, I'll leave the bug. 
