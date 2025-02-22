#ifndef COLLISION_H
#define COLLISION_H

#include "utils.h"
#include "ship.h"
#include "powerup.h"
#include "bullet.h"

#include <stdbool.h>

/**
 * @brief Checks for collisions between various game entities.
 *
 * This function checks for collisions between the bullets and ships, bullets and powerups, and ships and powerups.
 *
 * @param bulletRED A pointer to the bullet object fired by the red ship. The bullet object should have properties xx and yy which represent the x and y coordinates of the bullet.
 * @param bulletBLUE A pointer to the bullet object fired by the blue ship. The bullet object should have properties xx and yy which represent the x and y coordinates of the bullet.
 * @param red A pointer to the red ship object. The ship object should have properties xx and yy which represent the x and y coordinates of the ship.
 * @param blue A pointer to the blue ship object. The ship object should have properties xx and yy which represent the x and y coordinates of the ship.
 * @param led_line A pointer to a volatile uint32_t that represents the LED line. This could be used to indicate collisions or other game events.
 * @param powerup A pointer to the powerup object. The powerup object should have properties xx and yy which represent the x and y coordinates of the powerup.
 *
 * @return Returns true if a collision is detected, false otherwise.
 */
bool is_collision(bullet_t *bulletRED, bullet_t *bulletBLUE, ship_t *red, ship_t *blue, volatile uint32_t *led_line, powerup_t *powerup);

#endif