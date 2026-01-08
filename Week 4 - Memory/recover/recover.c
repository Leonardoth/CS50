#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int checkHeader(uint8_t buffer[BLOCK_SIZE]);

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }
    int jpgCounter = -1;
    char filename[sizeof(int) + 8];

    FILE *image;
    // Create a buffer for a block of data
    uint8_t buffer[BLOCK_SIZE];

    int recoveryStarted = 0;
    // While there's still data left to read from the memory card
    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // Create JPEGs from the data
        if (checkHeader(buffer))
        {
            // close previous file
            if (recoveryStarted)
            {
                fclose(image);
            }
            recoveryStarted = 1;
            // Jpeg count ++
            jpgCounter++;
            // new name
            sprintf(filename, "%03i.jpg", jpgCounter);
            // new JPG
            image = fopen(filename, "w");
            if (image == NULL)
            {
                printf("Could not open a new image. :( \n");
                return 1;
            }
            // start writing
            fwrite(buffer, 1, BLOCK_SIZE, image);
        }
        else
        {
            // invalid read of size 4! (probably first bytes/image == NULL)
            if (recoveryStarted)
            {
                fwrite(buffer, 1, BLOCK_SIZE, image);
            }
        }
    }

    fclose(image);
    fclose(card);
    return 0;
}

int checkHeader(uint8_t buffer[BLOCK_SIZE])
{
    int firstByte = buffer[0] == 0xff;
    int secondByte = buffer[1] == 0xd8;
    int thirdByte = buffer[2] == 0xff;
    int fourthByte = (buffer[3] & 0xf0) == 0xe0;

    if (firstByte && secondByte && thirdByte && fourthByte)
    {
        return 1;
    }

    return 0;
}
