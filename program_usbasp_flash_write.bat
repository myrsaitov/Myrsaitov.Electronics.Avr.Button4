avrdude.exe -c usbasp -p m32 -u -U flash:w:main.hex:i -U flash:v:main.hex:i -e -F
pause