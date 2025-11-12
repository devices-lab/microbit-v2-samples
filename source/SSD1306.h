#ifndef __SD1306_OBF_H
#define __SD1306_OBF_H

#include "MicroBit.h"
extern MicroBit uBit;

#define OLED_BLACK 0
#define OLED_WHITE 1
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define OLED_PIXELS_PER_PAGE 8
#define OLED_NUM_PAGES_PER_COL OLED_HEIGHT / OLED_PIXELS_PER_PAGE

void SSD1306_init();
void SSD1306_setPixel(uint8_t x, uint8_t y, uint8_t colour);
void SSD1306_clearColumn(uint8_t col);

#endif // !__SD1306_OBF_H
