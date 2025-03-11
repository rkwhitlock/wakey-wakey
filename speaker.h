// speaker.h

#ifndef SPEAKER_H
#define SPEAKER_H

#include "shared.h"

#define SPEAKER_MAC "37:4D:21:9B:D9:87"

void connectBluetoothSpeaker();
void playAudio(const char *filePath);
void body_speaker(SharedVariable *v);

#endif