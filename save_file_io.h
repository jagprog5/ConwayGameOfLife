#if !defined(SAVE_FILE_IO)
#define SAVE_FILE_IO
int writeSaveFile(char* file, int* grid, int width, int height);
int readSaveFile(char* file, int* width, int* height, int* grid);
#endif