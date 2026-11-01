// Modifies the volume of an audio file

#include <inttypes.h>
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

    // // TODO: Copy header from input file to output file

    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    //    uint16_t bits_per_sample =
    //     ((uint16_t)header[35] << 8) |
    //     header[34];

    //     uint32_t data_size =
    //         ((uint32_t)header[43] << 24) |
    //         ((uint32_t)header[42] << 16) |
    //         ((uint32_t)header[41] << 8)  |
    //         ((uint32_t)header[40]);

    //     printf("bits per sample: %u\n", bits_per_sample);
    //     printf("chunk: %.4s\n", &header[36]);
    //     printf("data size: %u\n", data_size);
    // TODO: Read samples from input file and write updated data to output file

    // Create a buffer for a single sample
    int16_t buffer;

    // Read single sample from input into buffer while there are samples left to read
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        // Update volume of sample
        buffer *= factor;

        // Write updated sample to new file
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
