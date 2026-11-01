#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    FILE *jpg = NULL;
    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    int fileNo = 0;

    int blockSize = 512;
    // Create a buffer for a block of data
    uint8_t buffer[blockSize];
    // While there's still data left to read from the memory card
    while (fread(buffer, 1, blockSize, card) == blockSize)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if (jpg)
            {
                fclose(jpg);
            }
            char filename[8];
            snprintf(filename, sizeof(filename), "%03i.jpg", fileNo++);
            jpg = fopen(filename, "wb");
        }

        if (jpg)
        {
            fwrite(&buffer, sizeof(buffer), 1, jpg);
        }
    }

    if (jpg)
    {
        fclose(jpg);
    }

    fclose(card);
}
