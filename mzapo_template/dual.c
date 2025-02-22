/*******************************************************************
  Project main function template for MicroZed based MZ_APO board
  designed by Petr Porazil at PiKRON
 
  include your name there and license for distribution.
  Authors: @palound @petrada6
 
 *******************************************************************/
 
#define _POSIX_C_SOURCE 200112L
 
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
#include <time.h>
#include <stdbool.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "draw_px_or_char.h"

#include "bullet.h"
#include "utils.h"
#include "ship.h"
#include "powerup.h"
#include "collision.h"

powerup_t fastership = {.xx = 240, .yy = 160, .color = COLOR_PURPLE, .visible = false};
powerup_t fastershot = {.xx = 200, .yy = 160, .color = COLOR_ORANGE, .visible = false};
powerup_t powershot = {.xx = 160, .yy = 160, .color = COLOR_WHITE, .visible = false};

ship_t red = {.xx = 5, .yy = 135, .color = COLOR_RED, .direction = RIGHT_DIRECTION, .is_reloaded = true, .last_shot = 3, .health = 15, .powerup = false};
ship_t blue = {.xx = 475, .yy = 135, .color = COLOR_BLUE, .direction = LEFT_DIRECTION, .is_reloaded = true, .last_shot = 3, .health = 240, .powerup = false};
bullet_t bulletRED = {.xx = 480, .yy = 0, .direction = RIGHT_DIRECTION, .speed = 1, .powerup_bullets = 0, .damage = 1};
bullet_t bulletBLUE = {.xx = -50, .yy = 0, .direction = LEFT_DIRECTION, .speed = 1, .powerup_bullets = 0, .damage = 1};


unsigned short *fb;

int led1_color = 0x0000FF00;
int led2_color = 0x0000FF00;

void pickup_powerup(powerup_t *powerup);


int main(int argc, char *argv[]) {
  unsigned char *parlcd_mem_base, *mem_base;
  int i,j;
  int ptr;
  unsigned int c;
  char counterRED = 0;
  char counterBLUE = 0;
  
  fb  = (unsigned short *)malloc(320*480*2);
  powerup_t tmp_pup;
  printf("Hello world\n");
  
 
  parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
  if (parlcd_mem_base == NULL)
    exit(1);
 
  mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  if (mem_base == NULL)
    exit(1);
 
  parlcd_hx8357_init(parlcd_mem_base);
 
  parlcd_write_cmd(parlcd_mem_base, 0x2c);
  ptr=0;
  for (i = 0; i < 320 ; i++) {
    for (j = 0; j < 480 ; j++) {
      c = 0;
      fb[ptr]=c;
      parlcd_write_data(parlcd_mem_base, fb[ptr++]);
    }
  }

 
  volatile uint32_t *led1 = (volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o);
  volatile uint32_t *led2 = (volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o);
  volatile uint32_t *led_line = (volatile uint32_t*)(mem_base + SPILED_REG_LED_LINE_o);
  *led_line = 0xF000000F;
  *led2 = 0x0000FF00;
  *led1 = 0x0000FF00;
  
  time_t starting_time = time(NULL);
  do {
    time_t current_time = time(NULL);
    int r = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

    *led_line = (red.health << 28) | blue.health >> 4;
    //GREEN BUTTON
    if (((r) & (1 << 25))!=0) {
      break;
    }

    blue.yy = ((r&0xff)*(-270))/256 + 270;
    red.yy = (((r>>16)&0xff)*270)/256;
    

    for (ptr = 0; ptr < 320*480 ; ptr++) {
        fb[ptr]=0u;
    }
    
    if(!is_collision(&bulletRED, &bulletBLUE, &red, &blue, led_line, &tmp_pup)) {
      render_bullet(&bulletRED);
      render_bullet(&bulletBLUE);
    }
    draw_ship(&red);
    draw_ship(&blue);
    
    
    if(difftime(current_time, starting_time) >= 4) {
      tmp_pup.color = choose_powerup();
      tmp_pup.xx = rand() % (425 - 50) + 50;
      tmp_pup.yy = rand() % (290 - 25);
      tmp_pup.visible = true;
      starting_time = current_time;
    }
    if (tmp_pup.visible) {
      draw_powerup(&tmp_pup);
    }
    
  // CERVENA LOD
    time_t current_timeRED = time(NULL);
    if (difftime(current_timeRED, red.last_shot) >= 3) {
      red.is_reloaded = true;
      if((r&(1 << 26))!=0) {
        printf("Strela cerveny\n");
        if(bulletRED.powerup_bullets == 0) {
          bulletRED.speed = 1;
          bulletRED.damage = 1;
        }
        if (bulletRED.powerup_bullets > 0){
          bulletRED.powerup_bullets--;
        }
        if(bulletRED.powerup_bullets == 0) {
          led1_color = 0x0000FF00;
        } 
        
        red.is_reloaded = false;
        red.last_shot = current_timeRED;
        bulletRED.xx = red.xx + 50;
        bulletRED.yy = red.yy + 20;
        draw_bullet(&bulletRED);
        
      }
      
      if (red.is_reloaded) {
        *led1 = led1_color;
      } else {
        *led1 = 0x00FF0000;
      }
    }

    // MODRA LOD
    time_t current_timeBLUE = time(NULL);

    if (difftime(current_timeBLUE, blue.last_shot) >= 3) {
      blue.is_reloaded = true;
      if((r& (1 << 24))!=0) {
        if (bulletBLUE.powerup_bullets == 0) {
          bulletBLUE.speed = 1;
          bulletBLUE.damage = 1;
        }

        if (bulletBLUE.powerup_bullets > 0) {
          bulletBLUE.powerup_bullets--;
        }
        if(bulletRED.powerup_bullets == 0) {
          led2_color = 0x0000FF00;
        }
        printf("%d\n", bulletBLUE.powerup_bullets);
        blue.is_reloaded = false;
        blue.last_shot = current_timeBLUE;
        bulletBLUE.xx = blue.xx - 50; //50
        bulletBLUE.yy = blue.yy + 20; //24
        draw_bullet(&bulletBLUE);
      }
      if (blue.is_reloaded) {
        *led2 = led2_color;
      } else {
        *led2 = 0x00FF0000;
      }
    }

    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (ptr = 1; ptr < 480*320 ; ptr+=2) {
        // Combine two bytes into a single 16-bit value
        uint32_t two_pixels = (fb[ptr] << 16) | fb[ptr];
      
        parlcd_write_data2x(parlcd_mem_base, two_pixels);
    }

    if(red.color == COLOR_WHITE) {
      counterRED++;
    }
    if (counterRED > 14) {
      red.color = COLOR_RED;
      counterRED = 0;
    }
    if (blue.color == COLOR_WHITE) {
      counterBLUE++;
    }
    if (counterBLUE > 14) {
      blue.color = COLOR_BLUE;
      counterBLUE = 0;
    }
    
    
  } while (red.health < 240 && blue.health > 15);
    
    ptr=0;
    for (i = 0; i < 320 ; i++) {
      for (j = 0; j < 480 ; j++) {
        c = 0;
        fb[ptr]=c;
        parlcd_write_data(parlcd_mem_base, fb[ptr++]);
      }
    }
    *led_line = 0xFFFFFFFF;
    

    if(red.health == 240){
      write_text(100, 135, "Vyhral modry", COLOR_BLUE, 3, 17);
      *led1 = 0x0000FF;
      *led2 = 0x0000FF;
    } else if (blue.health == 15) {
      write_text(80, 135, "Vyhral cerveny", COLOR_RED, 3, 17);
      *led1 = 0xFF0000;
      *led2 = 0xFF0000;
    } else {
      write_text(90, 135, "GAME ABORTED", COLOR_WHITE, 3, 17);
    }

    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (ptr = 1; ptr < 480*320 ; ptr+=2) {
        // Combine two bytes into a single 16-bit value
        uint32_t two_pixels = (fb[ptr] << 16) | fb[ptr];
        //uint32_t two_pixels = (uint32_t)& fb[ptr];
        parlcd_write_data2x(parlcd_mem_base, two_pixels);
    }

  return 0;
}

void pickup_powerup(powerup_t *powerup) {
  switch (powerup->color) {
    case COLOR_PURPLE:
      if (red.powerup) {
        led1_color = 0x800080;
        red.powerup = false;
        bulletRED.powerup_bullets = 1;
        bulletRED.speed = 1;
        bulletRED.damage = 2;
      } else if (blue.powerup) {
        led2_color = 0x800080;
        blue.powerup = false;
        bulletBLUE.powerup_bullets = 1;
        bulletBLUE.speed = 1;
        bulletBLUE.damage = 2;
      }
      break;
    case COLOR_ORANGE:
    //BULLET SPEED
      if (red.powerup) {
        led1_color = 0x8B4500;
        bulletRED.damage = 1;
        red.powerup = false;
        bulletRED.speed = 2;
        bulletRED.powerup_bullets = 3;
      } else if (blue.powerup) {
        led2_color = 0x8B4500;
        bulletBLUE.damage = 1;
        blue.powerup = false;
        bulletBLUE.speed = 2;
        bulletBLUE.powerup_bullets = 3;
      }
      break; 
    case COLOR_GREEN:
      if (red.health > 15 && red.powerup) {
        red.health = red.health >> 1;
        red.powerup = false;
      } else if (blue.health < 240 && blue.powerup) {
        blue.health = blue.health << 1;
        blue.powerup = false;
      }
      break;
  }
}
