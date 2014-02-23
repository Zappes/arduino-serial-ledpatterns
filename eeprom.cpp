/********************************************************************************************
 LED shifter EEPROM helper code
 
 This file contains code used for stroing LEDshifter patterns in the EEPROM so they can be
 restored after the Arduino has been reset or switched off.
 
 Program code by Gregor Ottmann, https://github.com/Zappes.
 
 This piece of code is public domain, this is the license: http://unlicense.org/UNLICENSE
 ********************************************************************************************/

#include <Arduino.h>
#include <avr/eeprom.h>
#include "eeprom.h"

void persistPatterns(byte *patterns, int patternCount) {
  EepromDescriptor desc = {EEPROM_MAGIC, patternCount};
  
  eeprom_write_block((const void*)&desc, (void*)0, sizeof(desc));
  eeprom_write_block((const void*)patterns, (void*)sizeof(desc), patternCount);
}

int restorePatterns(byte *patterns, int maxPatternCount) {
  EepromDescriptor desc = {0,0};
  
  eeprom_read_block((void*)&desc, (void*)0, sizeof(desc));
  
  int patternCount = 0;
  
  // only read patterns if the descriptor with the proper magic word was found. without this
  // check we might read senseless random garbage from an uninitialized EEPROM.
  if(desc.magic == EEPROM_MAGIC)
  {
    patternCount = min(desc.patternCount, maxPatternCount);
    eeprom_read_block((void*)patterns, (void*)sizeof(desc), patternCount);
  }
  
  return patternCount;
}
