#include "font_types.h"
#include "draw_px_or_char.h"

extern unsigned short *fb;
font_descriptor_t *fdes = &font_winFreeSystem14x16;

void draw_pixel_big(int x, int y, unsigned short color, int scale) {
  int i,j;
  for (i=0; i<scale; i++) {
    for (j=0; j<scale; j++) {
      draw_pixel2(x+i, y+j, color);
    }
  }
}

int char_width(int ch) {
  int width;
  if (!fdes->width) {
    width = fdes->maxwidth;
  } else {
    width = fdes->width[ch-fdes->firstchar];
  }
  return width;
}

void draw_char(int x, int y, char ch, unsigned short color, int scale) {
  int w = char_width(ch);
  const font_bits_t *ptr;
  if ((ch >= fdes->firstchar) && (ch-fdes->firstchar < fdes->size)) {
    if (fdes->offset) {
      ptr = &fdes->bits[fdes->offset[ch-fdes->firstchar]];
    } else {
      int bw = (fdes->maxwidth+15)/16;
      ptr = &fdes->bits[(ch-fdes->firstchar)*bw*fdes->height];
    }
    int i, j;
    for (i=0; i<fdes->height; i++) {
      font_bits_t val = *ptr;
      for (j=0; j<w; j++) {
        if ((val&0x8000)!=0) {
          draw_pixel_big(x+scale*j, y+scale*i, color, scale);
        }
        val<<=1;
      }
      ptr++;
    }
  }
}

void write_text(int x, int y, char text[], unsigned short color, int scale, int offset) {
    for (int i = 0; text[i] != '\0'; ++i) {
        draw_char(x,y, text[i], color, scale);
        x += char_width(text[i]) + offset;
        }
        x = 145;
}

void draw_pixel2(int x, int y, unsigned short color) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    fb[x+480*y] = color;
  }
}
