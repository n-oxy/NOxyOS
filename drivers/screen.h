#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

// vga i/o
#define SCREEN_BASE_CTRL 0x3d4 // 
#define SCREEN_BASE_DATA 0x3d5 // cursor = (+0x0e = high register - +0x0f = low register)

void lprint_at(char* base, int row, int col);
void lprint(char* base);
void clear_screen();