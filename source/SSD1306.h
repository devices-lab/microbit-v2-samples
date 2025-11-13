#ifndef __SD1306_OBF_H
#define __SD1306_OBF_H

#include "MicroBit.h"
extern MicroBit uBit;

#define OLED_PIXEL_ON true
#define OLED_PIXEL_OFF false
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

void SSD1306_init();
void SSD1306_setPixel(uint8_t x, uint8_t y, bool on);
void SSD1306_clearColumn(uint8_t col);

#endif // !__SD1306_OBF_H
