#ifndef DRAW_H
#define DRAW_H


void draw_pixel_big(int x, int y, unsigned short color, int scale);

int char_width(int ch);

void draw_char(int x, int y, char ch, unsigned short color, int scale);

void write_text(int x, int y, char text[], unsigned short color, int scale, int offset);

void draw_pixel2(int x, int y, unsigned short color);

#endif // DRAW_H
