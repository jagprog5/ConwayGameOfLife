#include <stdlib.h>

/**
 * @param bits Pointer to array of size 8.
 * Each int element must be a 0 or a 1.
 * Stores bits left to right with increasing array index.
 * @return A byte containing the bits.
 */
unsigned char bitsToByte(int* bits) {
    unsigned char out = 0;
    for (int i = 0; i < 8; ++i) {
        out += *(bits + i) << (7 - i);
    }
    return out;
}

/**
 * @return Pointer to array of integers with boolean values 0 and 1 corresponding to the input byte.
 * Increasing index corresponds with left to right bits in the byte.
 */
int* byteToBits(unsigned char byte) {
    int* bits = (int*)malloc(sizeof(int) * 8);
    for (int i = 0; i < 8; ++i) {
        *(bits + i) = (byte & (1 << (7 - i))) >> (7 - i);
    }
    return bits;
}