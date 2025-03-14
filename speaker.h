// speaker.h

#ifndef SPEAKER_H
#define SPEAKER_H

#include "shared.h"

#define SPEAKER_MAC "37:4D:21:9B:D9:87" // MAC address of the Bluetooth speaker

void connectBluetoothSpeaker();       // Connect to bluetooth speaker
void playAudio(const char *filePath); // Play audio file
void body_speaker(SharedVariable *v); // Speaker handler

#endif