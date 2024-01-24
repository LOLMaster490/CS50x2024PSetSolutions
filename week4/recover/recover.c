#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
const int BUFFERSIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    BYTE buffer[BUFFERSIZE];

    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    FILE *img;
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    bool isFirst = true;
    int photoNumber = 0;
    bool headerFound = false;

    while (fread(&buffer, 1, BUFFERSIZE, inptr) != 0)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (isFirst == false)
            {
                fclose(img);
            }
            headerFound = true;
            isFirst = false;
            char *filename = malloc(8);
            sprintf(filename, "%03i.jpg", photoNumber);
            img = fopen(filename, "w");
            free(filename);
            photoNumber++;
            fwrite(&buffer, 1, BUFFERSIZE, img);
        }
        else if (headerFound == true)
        {
            fwrite(&buffer, 1, BUFFERSIZE, img);
        }
    }
    fclose(inptr);
    fclose(img);
    return 0;
}
