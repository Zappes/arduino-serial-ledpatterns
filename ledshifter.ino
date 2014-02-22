/********************************************************************************************
 LED shifter
 
 This sketch reads commands from a serial line that define patterns which in turn are shifted
 out to an 74HC595 shift register connected to the Arduino. Think of it as one of those
 terribly annoying christmas flickerfucks, but you can control this one with bluetooth. :)
 
 Program code by Gregor Ottmann, https://github.com/Zappes.
 Inspiration from the tutorial at http://arduino.cc/en/tutorial/ShiftOut
 
 This piece of code is public domain, this is the license: http://unlicense.org/UNLICENSE
 ********************************************************************************************/

// Pin connected to ST_CP of 74HC595
#define LATCH_PIN 8
// Pin connected to SH_CP of 74HC595
#define CLOCK_PIN 12
// Pin connected to DS of 74HC595
#define DATA_PIN 11

// delay between patterns
#define DELAY 150

byte patterns[] = {
  0x81,
  0x42,
  0x24,
  0x18,
  0x24,
  0x42,
  0xff,
  0x00,
  0xff,
  0x00,
  0xff,
  0x00
};

void setup() {
  //set pins to output so you can control the shift register
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
}

void loop() {
  // count from 0 to 255 and display the number 
  // on the LEDs
  for (int i = 0; i < sizeof(patterns); i++) {
    // take the latchPin low so 
    writeToLeds(patterns[i]);
    // pause before next value:
    delay(DELAY);
  }
}

/*
  Writes the given byte out to the shift register and handles the latch pin properly
  while doing so.
*/
void writeToLeds(byte value) {
    // the LEDs don't change while you're sending in bits:
    digitalWrite(LATCH_PIN, LOW);

    // shift out the bits:
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, value);  

    //take the latch pin high so the LEDs will light up:
    digitalWrite(LATCH_PIN, HIGH);
}
