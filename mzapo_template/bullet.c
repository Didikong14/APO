#include "bullet.h"
#include "utils.h"


void draw_bullet(bullet_t *bullet) {
  int i, j;
  for (i=0; i<18; i++) {
    for (j = 0; j < 13; j++) {
      draw_pixel(i + bullet->xx, j + bullet->yy, COLOR_YELLOW);
    }
    
  }
}


void render_bullet(bullet_t *bullet) {
  bullet->xx += 10 * bullet->direction * bullet->speed;
  draw_bullet(bullet);
}