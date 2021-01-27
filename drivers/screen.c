#include "screen.h"

void print_char(char c, int col)
{
    char* video_memory = (char*)0xb8000;
    *(video_memory + (col * 2)) = c;
}
void clear_screen()
{
    int screenSize = MAX_COLS * MAX_ROWS;
    int i;
    char* screen = VIDEO_ADDRESS;

    for (i = 0; i < screenSize; i++) 
    {
        screen[i * 2] = ' ';
        screen[i * 2 + 1] = WHITE_ON_BLACK;
    }
}