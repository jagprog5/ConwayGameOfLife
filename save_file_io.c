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
    if (!dimValid(width, height)) return 0;
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
            if (valsRemaining == 0) break;
            // This will work even if the grid data does not perfectly fit into bytes,
            // aka width * height is not evenly divisible by 8.
            if (valsRemaining < 8) {
                int lastByte[] = {0, 0, 0, 0, 0, 0, 0, 0};
                for (int i = 0; i < valsRemaining; i++) {
                    lastByte[i] = *(walk + i);
                }
                unsigned char lastc = bitsToByte(lastByte);
                fwrite(&lastc, sizeof(char), 1, f);
                break;
            }
        }
        fclose(f);
        return 1;
    } else {
        return 0;
    }
}

int readSaveFile(char* file, int* width, int* height, int** grid) {
    FILE *f = fopen(file, "r"); // read mode only
    if (f) {
        *width = fgetc(f);
        *height = fgetc(f);
        *grid = (int*)malloc(sizeof(int) * *width * *height);
        int* walk = *grid;
        unsigned char c;
        while (1) {
            c = fgetc(f);
            int* bits = byteToBits(c);
            int valsRemaining = (int)*width * *height - (walk - *grid);
            for (int i = 0; i < (valsRemaining > 8 ? 8 : valsRemaining); ++i) {
                *(walk + i) = *(bits + i);
            }
            free(bits);
            if (valsRemaining <= 0) break;
            walk += 8;
        }
        fclose(f);
        return 1;
    } else {
        return 0;
    }
}

int dimValid(int width, int height) {
    if (width > 255 || height > 255 || width < 1 || height < 1) {
        // Preventing strange values from int cast to unsigned char
        puts("Grid dimensions are invalid! Width and height must be in range [1, 255]");
        return 0;
    }
    return 1;
}