#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "MicroBit.h"
/**
 * Neccessary to prevent NRF52SPI collision.
 */
#undef SPI

#include "ST7735.h"
#include "SPIScreenIO.h"

#define ST7735_HEIGHT 128
#define ST7735_WIDTH 160
#define PALETTE_LENGTH 16

/** Irrelevant I think. */
#define INPUT_PRIORITY 10
/** Draw stuff on the screen. */
#define RENDER_PRIORITY 30
/** Actually push to the screen. */
#define SCREEN_PRIORITY 100
/** For business logic. */
#define UPDATE_PRIORITY 20

void display_init();
void update_display();
void fill(uint8_t c);

void fill_display_loop();
void update_display_loop();
#endif
