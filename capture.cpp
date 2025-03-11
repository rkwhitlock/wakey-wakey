#include <cstdlib>
#include <iostream>

int main()
{
    std::cout << "Capturing image..." << std::endl;

    int result = system("libcamera-still -n -o image.jpg --width 1920 --height 1080");

    if (result == 0)
    {
        std::cout << "Image saved as image.jpg" << std::endl;
        FILE *fp;
        char result[1024];

        // Run Python script and capture output
        fp = popen("python3 pose_recognition.py", "r");
        if (fp == NULL)
        {
            perror("Error running Python script");
            return 1;
        }

        // Read output from Python script
        while (fgets(result, sizeof(result), fp) != NULL)
        {
            if (result == "1")
            {
                printf("success!!\n");
            }
            else
            {
                printf("not success\n");
            }
        }

        // Close the pipe
        pclose(fp);
    }
    else
    {
        std::cerr << "Error capturing image!" << std::endl;
    }

    return 0;
}
