#include<stdio.h>

int startsWith(char* prefix, char* fullString) {
    while (*prefix==*fullString) {
        prefix++;
        if (*prefix=='\0') return 1;
        fullString++;
    }
    return 0;
}

int numFromString(char* in, int* numStrLength) {
    // check for leading sign
    int leadingSign = *in == '-' || *in == '+';
    if (leadingSign) {
        // Ignore sign for now.
        in += 1;
    }
    
    int terminatorIndex = 0;
    char c;
    // any non-number character terminates the number string
    while ((c = *(in + terminatorIndex)) >= '0' && c <= '9') {
        ++terminatorIndex;
    }
    
    int total = 0;
    for (int i = terminatorIndex - 1; i > -1; --i) {
        int num = *(in + i) - '0';
        for (int j = 0; j < (terminatorIndex - 1) - i; ++j) {
            num *= 10;
        }
        total += num;
    }
    
    if (leadingSign && *(in - 1) == '-') {
        total *= -1;
    }
    
    if (numStrLength) { // NULL pointer for string length does nothing
        *numStrLength = terminatorIndex + (leadingSign ? 1 : 0);
    }
    
    return total;
}

int strLength(char* in) {
    char* walk = in;
    while (*walk++ != '\0') {}
    return walk - in - 1;
}

void setFileStrTerminator(char* file) {
    char* walk = file;
    // negative value for EOF. 0 for null char
    while (*walk != '\n' && *walk > 1) {
        walk++;
    }
    *walk = '\0';
}

/**
 * @brief Parses a list of decimal integer strings, separated by spaces
 * @param input The input string. e.g. "-42 15 1"
 * @param paramList Pointer to array of pointers to int parameters to b returned.
 * @param numParams Expected number of parameters.
 */
void parseParams(char* input, int** paramList, int numParams) {
    int lengths[numParams]; // last length is not used
    for (int i = 0; i < numParams; ++i) {
        lengths[i] = 0;
    }
    for (int i = 0; i < numParams; ++i) {
        // i number of spaces, aclTabCtrlnd the length of the previous numbers.
        int sumLength = i;
        for (int j = 0; j < i; ++j) {
            sumLength += lengths[j];
        }
        **(paramList+i) = numFromString(input + sumLength, &lengths[i]);
    }
}
