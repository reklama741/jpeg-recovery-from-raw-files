#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Give proper arguments");
        return 1;
    }
    else if (argc == 2)
    {
        FILE *file = fopen(argv[1], "r");
        BYTE buffer[512];
        int remaining_bytes;
        int jpgcounter = 0;
        char current_jpg[8];
        sprintf(current_jpg, "%03i.jpg", jpgcounter);
        FILE *file2 = fopen(current_jpg, "w");
        do
        {
            remaining_bytes = fread(&buffer, sizeof(BYTE), 512, file);

            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                if (jpgcounter == 0)
                {
                    fwrite(buffer, sizeof(BYTE), 512, file2);
                    jpgcounter++;
                }
                else
                {
                    fclose(file2);
                    sprintf(current_jpg, "%03i.jpg", jpgcounter);
                    file2 = fopen(current_jpg, "w");
                    fwrite(buffer, sizeof(BYTE), 512, file2);
                    jpgcounter++;
                }
            }
            else if (jpgcounter != 0)
            {
                fwrite(buffer, sizeof(BYTE), remaining_bytes, file2);
            }
        }
        while (remaining_bytes == 512);
        fclose(file);
        fclose(file2);
    }
}
