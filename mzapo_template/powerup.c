#include "powerup.h"
#include "ship.h"
#include "utils.h"
#include "bullet.h"


void draw_powerup(powerup_t *powerup){
  int i, j;
  for (i=0; i<15; i++) {
    for (j = 0; j < 15; j++) {
      draw_pixel(powerup->xx + i, powerup->yy + j, powerup->color);
    }
  }
}

