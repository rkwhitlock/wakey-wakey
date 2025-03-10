#include "pose.h"
#include "shared.h"
#include <stdio.h>
#include <string.h>

int check_pose()
{
    int result = system("libcamera-still -n -o image.jpg --width 1920 --height 1080");

    if (result == 0)
    {
        FILE *fp;
        char result[1024];

        // Run Python script and capture output
        fp = popen("python3 pose_recognition.py", "r");
        if (fp == NULL)
        {
            perror("Error running Python script");
            return 0;
        }

        // Read output from Python script
        while (fgets(result, sizeof(result), fp) != NULL)
        {
            if (strcmp(result, "1\n") == 0)
            {
                printf("SUCCESS\n");
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