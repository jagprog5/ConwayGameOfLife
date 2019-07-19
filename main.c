#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "save_file_io.h"
#include "conway.h"
#include "string_manipulation.h"

#define ESCAPE "escape"
#define RANDOM "random"
#define LOAD "load"
#define WRITE "write"
#define BLANK "blank"
#define TOGGLE "toggle"
#define NEXT "next"
#define PLAY "play"
#define HELP "help"
#define TESTFILE "..\\randtest.txt" //"C:\\Users\\johng\\OneDrive\\Desktop\\Test\\test.txt"

int main(int argc, char **argv)
{
    puts("---Simple Conway Game of Life Simulator---");
    puts("Try \"help\" for a commands list");
    
    int width;
    int height;
    int* grid = NULL;
    
    int escape = 0;
    while (!escape) {
        char input[64];
        fgets(input, 64, stdin);
        if (startsWith(ESCAPE, input)) {
            escape = 1;
        } else if (startsWith(RANDOM, input)) {
            int* params[] = {&width, &height};
            parseParams(input + strLength(RANDOM) + 1, params, 2);
            if (grid) {
                free(grid);
            }
            grid = getRandomGrid(width, height);
            drawGrid(grid, width, height, 0);
        } else if (startsWith(LOAD, input)) {
            char* file = input + strLength(LOAD) + 1;
            setFileStrTerminator(file);
            if (grid) {
                free(grid);
            }
            int status = readSaveFile(file, &width, &height, &grid);
            if (status) {
                printf("Loaded %d by %d grid:\n", width, height);
                drawGrid(grid, width, height, 0);
            } else {
                puts("Error loading file. Check the path.");
            }
        } else if (startsWith(WRITE, input)) {
            if (grid) {
                char* file = input + strLength(WRITE) + 1;
                setFileStrTerminator(file);
                int status = writeSaveFile(file, grid, width, height);
                if (status) {
                    puts("Grid was saved successfully!");
                } else {
                    puts("Error writing file!");
                }
            } else {
                puts("No grid is loaded to be written!");
            }
        } else if (startsWith(BLANK, input)) {
            int* params[] = {&width, &height};
            parseParams(input + strLength(BLANK) + 1, params, 2);
            if (!dimValid(width, height)) continue;
            if (grid) {
                free(grid);
            }
            grid = (int*)calloc(width * height, sizeof(int));
            drawGrid(grid, width, height, 0);
        } else if (startsWith(TOGGLE, input)) {
            if (grid) {
                int x;
                int y;
                int* params[] = {&x, &y};
                parseParams(input + strLength(TOGGLE) + 1, params, 2);
                if (x < 0 || y < 0 || x >=width || y >= height) {
                    puts("Invalid coordinates! Must be within bounds of the grid.");
                    continue;
                }
                *(grid + x + y * width) = !*(grid + x + y * width);
                drawGrid(grid, width, height, 0);
            } else {
                puts("No grid is loaded to be written!");
            }
        } else if (startsWith(NEXT, input)) {
            if (grid) {
                int* newGrid = getUpdatedGrid(grid, width, height);
                free(grid);
                grid = newGrid;
                drawGrid(grid, width, height, 0);
            } else {
                puts("No grid is available to update!");
            }
        } else if (startsWith(PLAY, input)) {
            if (grid) {
                int count;
                int delay;
                int* params[] = {&count, &delay};
                parseParams(input + strLength(PLAY) + 1, params, 2);
                if (count < 0 || delay < 0) {
                    puts("Count and delay must be greater than 0.");
                    continue;
                }
                for (int i = 0; i < count; ++i) {
                    int* newGrid = getUpdatedGrid(grid, width, height);
                    free(grid);
                    grid = newGrid;
                    drawGrid(grid, width, height, 1);
//                    putchar('\n');
                    Sleep(delay);
                }
            } else {
                puts("No grid is available to update!");
            }
        } else if (startsWith(HELP, input)) {
            puts("---Command List---");
            puts("random [width] [height]; generates a random grid with specified dimensions");
            puts("blank [width] [height]; generates a blank grid");
            puts("toggle [x] [y]; toggles a cell's state. Top left cell is at (0, 0).");
            puts("write [file path]; writes the grid to a file. e.g., for file in same dir, use \"..\\\\test.txt\"");
            puts("load [file path]; loads a grid that was saved with write");
            puts("escape; exits the program");
            puts("next; updates the grid");
            puts("play [count] [millisdelay]; repeatedly updates the grid, with a millisecond delay, and a certain # of frames. Interrupt by pressing any key.");
        }
    }
	return 0;
}
