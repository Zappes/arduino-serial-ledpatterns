/********************************************************************************************
 LED shifter
 
 This sketch reads commands from a serial line that define patterns which in turn are shifted
 out to an 74HC595 shift register connected to the Arduino. Think of it as one of those
 terribly annoying christmas flickerfucks, but you can control this one with bluetooth. :)
 
 The commands that come from serial are pretty simple: a row of hex encoded bytes. Those
 bytes are parsed and shifted out to the LEDs with 150ms delay between the different values.
 
 Try this one, it's quite pretty:
 010204081020408040201008040201008142241800ff00ff
 
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

// the serial port from which we read patterns
#define COMPORT Serial

// the speed of the serial port
#define COMSPEED 9600

// delay between patterns
#define DELAY 150

// the patterns parsed from the serial port will be stored here
// the pattern buffer size defines the maximum number of patterns
// that may be sent in a serial command.
#define PATTERN_BUFFER_SIZE 32
byte patternBuffer[PATTERN_BUFFER_SIZE];
byte patternCount;

// the commands coming from the serial port will be stored here
#define CMD_BUFFER_SIZE (PATTERN_BUFFER_SIZE*2)+1
char  commandBuffer[CMD_BUFFER_SIZE+1];
int   commandCursor = 0;

void setup() {
  //set pins to output so you can control the shift register
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  
  // switch off the LEDs
  writeToLeds(0);
  
  // start listening on the com port
  COMPORT.begin(COMSPEED);
  
}

void loop() {
  // we always look for a new pattern before each iteration. this means that
  // every pattern block will always be played to its end before a new one is
  // read and displayed.
  readPatternsFromSerial();
  
  // count from 0 to 255 and display the number 
  // on the LEDs
  for (int i = 0; i < patternCount; i++) {

    writeToLeds(patternBuffer[i]);
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

/*
  Parses a pattern string, i.e. a string of hex encoded bytes, and puts the bytes into the
  pattern buffer.
*/
void parsePatternsToBuffer(const char *input) {
  char currentByte[3];
  
  patternCount = 0;
  
  for(int i = 0; i < (strlen(input) / 2); i++)
  {
    currentByte[0] = *(input+(2*i));
    currentByte[1] = *(input+(2*i)+1);
    currentByte[2] = 0;
    
    patternBuffer[patternCount++] = strtol(currentByte, NULL, 16);
  }
}

/*
  Reads the pattern string from the serial port.
*/
void readPatternsFromSerial() {
  while(COMPORT.available())
  {
    char current = (char)COMPORT.read();

    // if the maximum command length is reached or if the command is terminated with a new line
    // character, the command buffer is terminated with a 0 chat and the command processing
    // routine is called.    
    if(commandCursor >= CMD_BUFFER_SIZE || current == 10 || current == 13) {
      commandBuffer[commandCursor] = 0;
      commandCursor = 0;

      parsePatternsToBuffer(commandBuffer);
    }
    else
    {
      commandBuffer[commandCursor++] = current;
    }
  }
}
