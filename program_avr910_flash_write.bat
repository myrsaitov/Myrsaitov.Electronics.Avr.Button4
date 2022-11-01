avrdude.exe -p m32 -c avr910 -P com3 -U flash:w:main.hex:i -U flash:v:main.hex:i -e -F





REM avrdude -u -p atmega32 -P com3 -c avr109 -b 19200 -v -U flash:w:main.hex 
REM avrdude -c usbasp -p atmega32 -U flash:w:main.hex


REM -U lfuse:w:0xbf:m -U hfuse:w:0xdf:m
REM BODEN=0; SPIEN=0; 


pause