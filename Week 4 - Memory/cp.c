#include <stdio.h>
#include <stdint.h>

// this replicates how windows treat a BYTE
typedef uint8_t BYTE;


int main(int argc, char *argv[])
{
    // the "b" means to do it in binary, because we want to copy them without changing anything
    FILE *src = fopen(argv[1], "rb");
    FILE *dst = fopen(argv[2], "wb");

    BYTE b;

    // while fread iterates over the file src byte by byte
    while(fread(&b, sizeof(b), 1, src) != 0)
    {
        fwrite(&b, sizeof(b), 1, dst);
    }

    fclose(dst);
    fclose(src);
}




