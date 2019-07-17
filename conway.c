#include <stdlib.h>

int* getUpdatedGrid(int* grid, int width, int height) {
    int* newGrid = (int*)malloc(sizeof(int) * width * height);
    for (int i = 0; i < width * height; ++i) {
        // https://en.wikipedia.org/wiki/Moore_neighborhood
        int mooreCount = 0;
        for (int j = -1; j < 2; j++) {
            for (int k = -1; k < 2; k++) {
                int checkIndex = i + j + k * width;
                // A very ugly if statement...
                // i is the current index in the grid being updated.
                // j (left and right), and k (up and down) iterate through
                // the moore neighbourhood surrounding index i.
                // The surrounding index is invalid if it is off the grid,
                // or the same index that is being updated.
                if (!(j==0 && k==0) && // surrounding index is the same as the updating index
                    checkIndex > -1 && // above grid
                    checkIndex < width * height && // below grid
                    !(i % width == 0 && j == -1) && // left of grid
                    !((i + 1) % width == 0 && j == 1)) { // right of grid
                    mooreCount += grid[checkIndex];
                }
            }
            if (*(grid + i)) {
                // if updating index is alive
                *(newGrid + i) = mooreCount == 2 || mooreCount == 3;
            } else {
                // if dead
                *(newGrid + i) = mooreCount == 3;
            }
        }
    }
    return newGrid;
}