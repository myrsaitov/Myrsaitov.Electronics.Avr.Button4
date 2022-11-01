avrdude.exe -c usbasp -p m32 -U lfuse:r:low_fuse_val.hex:h -U hfuse:r:high_fuse_val.hex:h

pause