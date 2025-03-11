#include <cstdlib>
#include <iostream>
#include <string>
#include <unistd.h>

// Change this to your Bluetooth speaker's MAC address
#define SPEAKER_MAC "EC:81:93:F7:36:6C"

void connectBluetoothSpeaker()
{
    std::string cmd = "bluetoothctl connect " + std::string(SPEAKER_MAC);
    std::cout << "Connecting to Bluetooth speaker..." << std::endl;
    int result = system(cmd.c_str());

    if (result == 0)
    {
        std::cout << "Connected successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Failed to connect to speaker!" << std::endl;
    }
}

void playAudio(const std::string &filePath)
{
    std::cout << "Playing audio: " << filePath << std::endl;
    std::string cmd = "mpg123 " + filePath;
    system(cmd.c_str());
}

int main()
{
    connectBluetoothSpeaker();

    sleep(2); // Give time for connection

    playAudio(
        "mixkit-crickets-and-insects-in-the-wild-ambience-39.mp3"); // Change this to your file
    return 0;
}

// compile and run
// g++ -o bluetooth_audio bluetooth_audio.cpp
// ./bluetooth_audio