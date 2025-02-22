#ifndef SHIP_H
#define SHIP_H
#include "utils.h"

#include <stdbool.h>
#include <time.h>
#include <stdint.h>

typedef struct {
  const uint32_t xx;
  uint32_t yy;
  unsigned short color;
  const short direction;
  bool is_reloaded;
  time_t last_shot;
  short health;
  bool powerup;
} ship_t;


/**
 * @brief Function to draw a ship
 * 
*/
void draw_ship(ship_t *ship);

#endif