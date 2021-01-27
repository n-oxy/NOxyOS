#include "ports.h"
#include "screen.h"

// declarations //

void print_c(char c, int row, int col);
int get_cursor_pos();
void set_cursor_pos(int offset); 

// externals //

void lprint(char* base)
{
    for(int i = 0; base[i] != 0; i++)
    {
        print_c(base[i], -1, -1);
    }
}
void lprint_at(char* base, int row, int col)
{
    for (int i = 0; base[i] != 0; i++)
    {
        print_c(base[i], row, col + i);
    }
}
void clear_screen()
{
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    unsigned char* screen = (unsigned char*)VIDEO_ADDRESS;
    for (i = 0; i < screen_size; i++)
    {
        screen[i * 2] = ' ';
        screen[i * 2 + 1] = WHITE_ON_BLACK;
    }
    set_cursor_pos(0);
}

// internals //

void print_c(char c, int row, int col)
{
    unsigned char* video_memory = (unsigned char*)VIDEO_ADDRESS;
    int offset = get_cursor_pos();
    if (row > -1 && col > -1)
    {
        offset = 2 * (row * MAX_COLS + col);
    }
    if (c == '\n')
    {
        offset = MAX_COLS * 2;
    }
    set_cursor_pos(offset + 2);
    video_memory[offset] = c;
    video_memory[offset + 1] = WHITE_ON_BLACK;
}
int get_cursor_pos()
{
    port_byte_out(SCREEN_BASE_CTRL, 0x0e);
    int offset = port_byte_in(SCREEN_BASE_DATA) << 8;
    port_byte_out(SCREEN_BASE_CTRL, 0x0f);
    offset += port_byte_in(SCREEN_BASE_DATA);
    return offset * 2;
}
void set_cursor_pos(int offset)
{
    offset /= 2;
    port_byte_out(SCREEN_BASE_CTRL, 0x0e);
    port_byte_out(SCREEN_BASE_DATA, (unsigned char)(offset >> 8));
    port_byte_out(SCREEN_BASE_CTRL, 0x0f);
    port_byte_out(SCREEN_BASE_DATA, (unsigned char)(offset & 0xff));
}