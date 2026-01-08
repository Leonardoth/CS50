// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    int *b = malloc(HEADER_SIZE * sizeof(uint8_t));
    if (b == NULL)
    {
        return 1;
    }
    // TODO: Copy header from input file to output file
    fread(b, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(b, sizeof(uint8_t), HEADER_SIZE, output);
    free(b);

    int16_t byte_2;
    int16_t buffer;
    // // TODO: Read samples from input file and write updated data to output file
    while (fread(&byte_2, sizeof(byte_2), 1, input) != 0)
    {
        byte_2 *= factor;
        buffer = byte_2;
        fwrite(&buffer, sizeof(buffer), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
