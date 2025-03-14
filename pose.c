// pose.c
#include "pose.h"
#include "shared.h"
#include <stdio.h>
#include <string.h>

// Function to check the user's pose using an external Python script
int check_pose()
{
    // Capture an image using the Raspberry Pi camera with specific resolution
    int result = system("libcamera-still -n -o image.jpg --width 1920 --height 1080");

    if (result == 0) // Check if the image capture was successful
    {
        FILE *fp;
        char result[1024]; // Buffer to store the output of the Python script

        // Run Python script and capture output
        fp = popen("python3 pose_recognition.py", "r");
        if (fp == NULL)
        {
            perror("Error running Python script");
            return 0; // Return failure if script execution fails
        }

        // Read output from Python script
        while (fgets(result, sizeof(result), fp) != NULL)
        {
            // If the output matches "1\n", the pose is recognized successfully
            if (strcmp(result, "1\n") == 0)
            {
                printf("SUCCESS: %s\n", result);
                return 1;
            }
            else
            {
                printf("not success: %s\n", result);
                return 0;
            }
        }

        // Close the pipe
        pclose(fp);
    }
    else
    {
        printf("error :(");
        return 0;
    }

    return 0;
}