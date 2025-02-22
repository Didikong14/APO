#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include "powerup.h"
#include "ship.h"
#include "bullet.h"


#define LEFT_DIRECTION -1
#define RIGHT_DIRECTION 1

#define COLOR_BLUE 0x7ff
#define COLOR_RED 0xF800
#define COLOR_YELLOW 0xFFE0
#define COLOR_GREEN 0x07E0
#define COLOR_WHITE 0xFFFF
#define COLOR_PURPLE 0xF81F
#define COLOR_ORANGE 0xFD20

extern int i, j;
extern unsigned char *parlcd_mem_base;
extern unsigned short *fb;



/**
 * @brief Function to draw a pixel
 * Function that is used to draw a pixel on the screen, it is using everytime we are drawing something
*/
void draw_pixel(int x, int y, unsigned short color);

/**
 * @brief Function to choose a powerup
 * Function that is used to choose a powerup color randomly
*/
unsigned short choose_powerup();

/**
 * @brief Function to get the maximum of two numbers
*/
int my_fmax(int a, int b);


#endif
