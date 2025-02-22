#ifndef BULLET_H
#define BULLET_H

#include <stdint.h>

#define COLOR_YELLOW 0xFFE0

typedef struct {
  uint32_t xx;
  uint32_t yy;
  const short direction;
  char speed;
  char powerup_bullets;
  char damage;
} bullet_t;


/**
 * @brief Function to draw a bullet
 * 
 * @param bullet A pointer to the bullet object to be drawn. The bullet object should have properties xx and yy which represent the x and y coordinates of the bullet.
 * 
 * This function iterates over a 18x13 grid, drawing a pixel at each point in the grid offset by the bullet's coordinates. The color of the pixel is set to yellow.
 */

void draw_bullet(bullet_t *bullet);

/**
 * @brief Function to update the bullet's position and render it
 * 
 * @param bullet A pointer to the bullet object to be updated and rendered. The bullet object should have properties xx, direction, and speed which represent the x coordinate, direction, and speed of the bullet respectively.
 * 
 * This function updates the bullet's x coordinate based on its direction and speed, then calls the draw_bullet function to render the bullet at its new position.
 */
void render_bullet(bullet_t *bullet);

#endif // BULLET_H