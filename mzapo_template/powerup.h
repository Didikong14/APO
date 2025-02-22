#ifndef POWERUP_H
#define POWERUP_H

#include "utils.h"
#include "ship.h"
#include "bullet.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  uint32_t xx;
  uint32_t yy;
  unsigned short color;
  bool visible;
} powerup_t;

/**
 * @brief Function to draw a powerup
 * It draws the powerup on the screen
*/
void draw_powerup(powerup_t *powerup);





#endif