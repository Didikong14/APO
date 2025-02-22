#include "utils.h"

#include <time.h>

extern unsigned short *fb;


void draw_pixel(int x, int y, unsigned short color) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    fb[x+480*y] = color;
  }
}

int my_fmax(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

unsigned short choose_powerup(){
  srand(time(NULL)); // seed the random number generator
  int random_number = rand() % 4 + 1; // generate a random number between 1 and 4

  switch (random_number)
  {
  case 1:
    return COLOR_PURPLE;
  case 2:
    return COLOR_ORANGE;
  case 3:
    return COLOR_GREEN;
  default:
    break;
  }
  return 0;
}

