# PIC18F47Q84-Simple-Audio-Synthesizer
Demonstrates usage of PIC18F47Q84 DAC to output different wave forms (sine, triangle, square) of varying frequencies based on user input with a ADC. 
Uses timer and a look up table to set the frequency and shape of signal. Look up table created with python to emulate common functions triangle, sine, and square. 

Demo video of perfomance can be seen here https://drive.google.com/file/d/1z4gbhRSj-T_-KLhEt9F4A216EkMIxYua/view?usp=sharing. The speaker is most responsive to a square wave so the octave change with the potentiometer knob is shown in square wave mode. The button clicking at the start is changing the wave type between the three options. 

Purpose of this project is to introduce myself to working with the PIC microcontroller for future projects. The dev board shown in the demo video is soldered by me. Future work for this would be to buy a higher current power amplifier for the voltage follower because the current limit required me to put in a limiting resistor making the sine and triangle waves quieter than ideal.  
