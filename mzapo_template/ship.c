#include "ship.h"
#include "utils.h"

void draw_ship(ship_t *ship){
  int i,j;
    // Ship
    for (j=0; j<=25; j++) {
        for (i=0; i<j*2; i++) {
          draw_pixel((ship->direction * i) + ship->xx,j+ship->yy,ship->color); // Right side of the triangle
        }
        for (i=0; i < j*2; i++) {
          draw_pixel((ship->direction * i) + ship->xx,(50 - j)+ ship->yy, ship->color); // Left side of the triangle
        }
    }
}
