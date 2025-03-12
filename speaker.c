// sudo apt-get install mpg123
#include "speaker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function to connect to the Bluetooth speaker
void connectBluetoothSpeaker()
{
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "bluetoothctl connect %s", SPEAKER_MAC);

    printf("Connecting to Bluetooth speaker...\n");

    // Use system() to run the bluetoothctl connect command
    int result = system(cmd);

    // Check if the connection was successful
    if (result == 0)
    {
        printf("Connected successfully!\n");
    }
    else
    {
        fprintf(stderr, "Failed to connect to speaker!\n");
    }
}

// Function to play the audio file
void playAudio(const char *filePath)
{
    printf("Playing audio: %s\n", filePath);
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "mpg123 %s", filePath);

    // Use system() to run the mpg123 command to play the audio file
    int result = system(cmd);

    // Check if the audio was played successfully
    if (result != 0)
    {
        fprintf(stderr, "Failed to play the audio file!\n");
    }
}

void body_speaker(SharedVariable *v)
{
    // Connect to the Bluetooth speaker
    connectBluetoothSpeaker();

    // Wait for 2 seconds to ensure the connection is made
    sleep(2);

    // Play the audio file after the connection is made
    while (1)
    {
        if (v->alarm)
        {
            playAudio("rooster.mp3");
        }
        delay(4);
    }
}
