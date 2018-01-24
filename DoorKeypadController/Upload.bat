avrdude -p 2313 -P com3 -c avrisp -b 19200 -v -U flash:w:Build\DoorKeypadController.hex
pause