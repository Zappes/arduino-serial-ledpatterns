Play Patterns on LEDs With Bluetooth Control
============================================

What Is this?
-------------
This Arduino sketch builds up on the tutorial for shift registers that can be found at http://arduino.cc/en/tutorial/ShiftOut. It adds code that listens on a serial connection for strings that can be parsed into patterns that should be played on a row of LEDs attached to the Arduino.

If you want to see this in action, have a lok here: http://www.youtube.com/watch?v=WX1ofkRAVps

The current pattern list will be stored in the Arduino's EEPROM and retrieved when powering up the next time, so one doesn't have to reprogram the patterns after powering down the chip.

Hardware
--------
For the example to work, you need two things:

* A serial line that's connected to some kind of terminal emulator. For debugging I used the built-in serial port over USB, but then I switched to a bluetooth module, which was really simple and a lot more satisfying to toy around with. For Linux users, I recommend using "minicom" as a terminal emulator. For Windows and Mac OS X, I recommend switching to Linux.
* The hardware setup from the shift register tutorial at http://arduino.cc/en/tutorial/ShiftOut, i.e. a 74HC595 shift register wired up to the arduino and 8 LEDs hooked up to that register.

The source code assumes that you have an Arduino Mega with a bluetooth module attached to serial 1 (pins 18/19). If you have an UNO or want to communicate using the USB connection, locate this line:

    #define COMPORT Serial1

Change that line to use "Serial" instead of "Serial1" and you're set.

Supported Commands
------------------
There's not much supported stuff here. Just send a string of hex-encoded bytes over the serial line and look what happens. I suggest trying this one for fun:

     010204081020408040201008040201008142241800ff00ff



