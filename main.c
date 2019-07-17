#include <stdio.h>
#include <stdlib.h>
#include "save_file_io.h"
#define TESTFILE "C:\\Users\\johng\\OneDrive\\Desktop\\Test\\test.txt"

int main(int argc, char **argv)
{
    int data[] =   {0, 1, 0,
                    0, 1, 0,
                    0, 1, 0};
    int* grid = data;
    writeSaveFile(TESTFILE, grid, 3, 3);
    int width;
    int height;
    readSaveFile(TESTFILE, &width, &height, grid);
    
    int* newGrid = getUpdatedGrid(grid, 3, 3);
    free(grid);
    grid = newGrid;
    for (int i = 0; i < 9; ++i) {
        if (i % 3 == 0) {
            putchar('\n');
        }
        printf("%d", *(grid + i));
    }
    putchar('\n');
	return 0;
}
