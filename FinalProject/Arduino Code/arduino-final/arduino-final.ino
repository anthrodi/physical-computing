*
NFC Game - Final Project
Anth Rodi
DIGF2B03 Physical Computing
OCAD University
Created on 04/08/15

Based on:

Reference Code, Elecrow NFC Shield Wiki, http://www.elecrow.com/wiki/index.php?title=NFC_Shield

*/

#include <PN532.h>
#include <SPI.h>

#define PN532_CS 10
PN532 nfc(PN532_CS);
#define  NFC_DEMO_DEBUG 1

//set Vibe Motor to Pin 4
int vibe = 4;

void setup(void) { 

pinMode(vibe,OUTPUT);
digitalWrite(vibe,LOW);

#ifdef NFC_DEMO_DEBUG
  Serial.begin(9600);
  Serial.println("Hello!");
#endif
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
#ifdef NFC_DEMO_DEBUG
    Serial.print("Didn't find PN53x board");
#endif
    while (1); // halt
  }
#ifdef NFC_DEMO_DEBUG
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); 
  Serial.println((versiondata>>24) & 0xFF, HEX);
  Serial.print("Firmware ver. "); 
  Serial.print((versiondata>>16) & 0xFF, DEC);
  Serial.print('.'); 
  Serial.println((versiondata>>8) & 0xFF, DEC);
  Serial.print("Supports "); 
  Serial.println(versiondata & 0xFF, HEX);
#endif
  // configure board to read RFID tags and cards
  nfc.SAMConfig();
}


void loop(void) {
  uint32_t id;
  // look for MiFare type cards
  id = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A);

  if (id == 3296227291) {
    Serial.print("Yay that's the one!");
    Serial.write(21); //For Unity Script
    Serial.flush(); //For Unity stability
    delay(500);
 
    
    digitalWrite(vibe, HIGH);
    delay(500);
    digitalWrite(vibe,LOW);
  
  }
  else {
    
  digitalWrite(vibe,LOW);
  
  }
  
  if (id == 1948510015) {
    Serial.print("That's the other one!");
    Serial.write(22); //For Unity script
    Serial.flush(); //For stability in Unity
    delay(500);
    
    
    digitalWrite(vibe,HIGH);
    delay(300);
    digitalWrite(vibe,LOW);
    delay(300);
    digitalWrite(vibe,HIGH);
    delay(300);
    digitalWrite(vibe,LOW);
    
  }
  else {
  
    digitalWrite(vibe,LOW);
  }
  
  
  
}
