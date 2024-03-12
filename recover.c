#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int a = 0;
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    FILE *img = NULL;
    FILE *card = fopen(argv[1], "r");
    char filename[8];
    uint8_t buffer[512];
    while (fread(buffer, 1, 512, card) == 512)
    {
        // ALL the .jpg start with 0xff, 0xd8, 0xff AND FROM 0xf0 to 0xe0
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (a > 0)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", a);
            img = fopen(filename, "w");
            a++;
        }
        if (img != NULL)
        {
            fwrite(buffer, 512, 1, img);
        }
    }
    fclose(card);
    if (img != NULL)
    {
        fclose(img);
    }
    return 0;
}
