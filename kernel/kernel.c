#include "../drivers/screen.h"
#include "../lib/util.h"
void start()
{
    clear_screen();
    char str[] = "ur mum\nabc";
    lprint(str);
}
