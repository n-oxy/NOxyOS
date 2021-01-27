#include "../drivers/screen.h"
#include "../lib/util.h"
void start()
{
    clear_screen();
    char str[16];
    int_to_ascii(123456789, str);
    lprint(str);
}