#if !defined(STRING_MANIPULATION)
#define STRING_MANIPULATION
int startsWith(char* prefix, char* fullString);
int numFromString(char* in, int* numStrLength);
int strLength(char* in);
void setFileStrTerminator(char* file);
void parseParams(char* input, int** paramList, int numParams);
#endif