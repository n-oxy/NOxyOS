#include "ports.h"
#include "screen.h"

// declarations //

int print_c(char c, int row, int col);
int get_cursor_pos();
void set_cursor_pos(int offset); 
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

// externals //

void lprint_at(char* base, int row, int col)
{
    int offset;
    if (col > -1 && row > -1)
        offset = get_offset(col, row);
    else
    {
        offset = get_cursor_pos();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
    for (int i = 0; base[i] != 0; i++)
    {
        offset = print_c(base[i], row, col);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}
void lprint(char* base)
{
    lprint_at(base, -1, -1);
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

int print_c(char c, int row, int col)
{
    unsigned char* video_memory = (unsigned char*)VIDEO_ADDRESS;
    int offset = get_cursor_pos();
    if (row > -1 && col > -1)
        offset = get_offset(col, row);
    if (c == '\n')
    {
        row = get_offset_row(offset);
        offset = get_offset(0, row + 1);
    }
    else
    {
        video_memory[offset] = c;
        video_memory[offset + 1] = WHITE_ON_BLACK;
        offset += 2;
    }
    set_cursor_pos(offset);
    return offset;
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

int get_offset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2; }