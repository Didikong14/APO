#include "collision.h"
#include "bullet.h"  

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


bool is_collision(bullet_t *bulletRED, bullet_t *bulletBLUE, ship_t *red, ship_t *blue, volatile uint32_t *led_line, powerup_t *powerup) {
  //RED SHIP COLLISON
  if (bulletBLUE->xx >= red->xx && bulletBLUE->xx <= red->xx + 50 && bulletBLUE->yy >= my_fmax(red->yy - 10, 0) && bulletBLUE->yy <= red->yy + 50) {
    printf("Trefa cerveneho\n");
    //led_line[(int)red->health] = 0;
    red->health = red->health << bulletBLUE->damage;
    printf("Health: %d\n", red->health);
    bulletBLUE->xx = -50;
    bulletBLUE->yy = 0;
    red->color = COLOR_WHITE;
    return true;
  }
  //BLUE SHIP COLLISION
  if(bulletRED->xx >= blue->xx - 70 && bulletRED->xx <= blue->xx && bulletRED->yy >= my_fmax(blue->yy - 10, 0) && bulletRED->yy <= blue->yy + 50) {
    printf("Trefa modreho\n");
    blue->health = blue->health >> bulletRED->damage;
    printf("Health: %d\n", blue->health);
    bulletRED->xx = 480;
    bulletRED->yy = 0;
    blue->color = COLOR_WHITE;
    return true;
  }

  //BULLET COLLISION
  for (int i = 0; i < 18; i++) {
    for (int j = 0; j < 13; j++) {
      if (bulletRED->xx + i == bulletBLUE->xx && bulletRED->yy + j == bulletBLUE->yy) {
          bulletRED->xx = 480;
          bulletRED->yy = 0;
          bulletBLUE->xx = -50;
          bulletBLUE->yy = 0;
          return true;
      }
      if (bulletRED->xx == bulletBLUE->xx + i && bulletRED->yy == bulletBLUE->yy + j) {
          bulletRED->xx = 480;
          bulletRED->yy = 0;
          bulletBLUE->xx = -50;
          bulletBLUE->yy = 0;
          return true;
      }
    }
  }

  //POWERUP COLLISION
  if (powerup->visible) {
    if (bulletRED->xx >= powerup->xx -14 && bulletRED->xx <= powerup->xx && bulletRED->yy >= powerup->yy - 14 && bulletRED->yy <= powerup->yy + 14) {
      printf("Powerup cerveny\n");
      bulletRED->xx = 480;
      bulletRED->yy = 0;
      powerup->visible = false;
      red->powerup = true;
      pickup_powerup(powerup);
      return true;
    }

    if (bulletBLUE->xx >= powerup->xx -14 && bulletBLUE->xx <= powerup->xx && bulletBLUE->yy >= powerup->yy - 14 && bulletBLUE->yy <= powerup->yy + 14) {
      printf("Powerup modry\n");
      bulletBLUE->xx = -50;
      bulletBLUE->yy = 0;
      powerup->visible = false;
      blue->powerup = true;
      pickup_powerup(powerup);
      return true;
    }
  }

  return false; 
}

