#include <stdio.h>
#include <stdlib.h>
#include "bit_storage.h"

/**
 * @brief The save file has the format: width byte, height byte, data to fill grid.
 * @param file
 * @param grid
 * @param width Width of grid [0, 255].
 * @param height Height of grid [0, 255]
 * @return Boolean value, 0 if failed.
 */
int writeSaveFile(char* file, int* grid, int width, int height) {
    if (width > 255 || height > 255 || width < 0 || height < 0) {
        // Preventing strange values from int cast to unsigned char
        puts("Grid dimensions are invalid! Width and height must be in range [0, 255]");
    }
    FILE *f = fopen(file, "w+"); // empty existing file
    if (f) {
        fwrite(&width, sizeof(char), 1, f);
        fwrite(&height, sizeof(char), 1, f);
        int* walk = grid;
        while (1) {
            unsigned char c = bitsToByte(walk);
            fwrite(&c, sizeof(char), 1, f);
            walk += 8;
            int valsRemaining = (int)width * height - (walk - grid);
            if (valsRemaining <= 0) break;
            // This will work even if the grid data does not perfectly fit into bytes,
            // aka width * height is not evenly divisible by 8.
            // The save file will not be looking at the trailing junk bits in the last byte anyway.
        }
        fclose(f);
        return 1;
    } else {
        printf("Error writing to file: %s", file);
        return 0;
    }
}

int readSaveFile(char* file, int* width, int* height, int* grid) {
    FILE *f = fopen(file, "r"); // read mode only
    if (f) {
        *width = fgetc(f);
        *height = fgetc(f);
        int* grid = (int*)malloc(sizeof(int) * *width * *height);
        int* walk = grid;
        unsigned char c;
        while (1) {
            c = fgetc(f);
            int* bits = byteToBits(c);
            int valsRemaining = (int)*width * *height - (walk - grid);
            for (int i = 0; i < (valsRemaining > 8 ? 8 : valsRemaining); ++i) {
                *(walk + i) = *(bits + i);
            }
            free(bits);
            walk += 8;
            if (valsRemaining<=0) break;
        }
        fclose(f);
        return 1;
    } else {
        printf("Error opening file: %s", file);
        return 0;
    }
}