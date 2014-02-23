/********************************************************************************************
 LED shifter EEPROM helper code
 
 This file contains code used for stroing LEDshifter patterns in the EEPROM so they can be
 restored after the Arduino has been reset or switched off.
 
 Program code by Gregor Ottmann, https://github.com/Zappes.
 
 This piece of code is public domain, this is the license: http://unlicense.org/UNLICENSE
 ********************************************************************************************/

#ifndef _EEPROM_H
#define _EEPROM_H

#include <Arduino.h>

// when reading state from the eeprom, this must be the value of the first 2 bytes. if it isn't, the eeprom
// is assumed to contain no usable pattern.
#define EEPROM_MAGIC 0xAFFE

// this struct is used for storing a simple descriptor in the eeprom.
typedef struct EepromDescriptor {
  int magic;
  int patternCount;
};

/**
 * Writes the descriptor followed by the actual pattern bytes to the EEPROM.
 *
 * @param patterns A pointer to the bytes to be stored.
 * @param patternCount The number of bytes that should be written.
 */
void persistPatterns(byte *patterns, int patternCount);

/**
 * Reads pattern bytes from the EEPROM.
 *
 * @param patterns A pointer to the pattern buffer to which the patterns should be
 *                 written.
 * @param maxPatternCount The maximum number of bytes that should be read. If,
 *                        according to the descriptor, less bytes are present in
 *                        the EEPROM, then only that number will be read.
 * @return The number of bytes that was read from the EEPROM.                        
 */
int restorePatterns(byte *patterns, int maxPatternCount);

#endif

