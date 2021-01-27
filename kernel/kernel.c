#include "../drivers/screen.h"
void start()
{
    clear_screen();
    char str[] = "cum!";
    for (int i = 0; i < sizeof(str) - 1; i++)
    {
        print_char(str[i], i);
    }
}