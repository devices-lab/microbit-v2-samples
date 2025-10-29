#include "display.h"

MicroBit uBit;

// Core pins for peripheral
NRF52Pin &sck = uBit.io.P13;
NRF52Pin &mosi = uBit.io.P15;
NRF52Pin &rst = uBit.io.P16;
NRF52Pin &dc = uBit.io.P8;

// unused pins, redirected to P0/P1 for debug
NRF52Pin &cs = uBit.io.P0;
NRF52Pin &miso = uBit.io.P1;

NRF52SPI *spi = new NRF52SPI(mosi, miso, sck);
SPIScreenIO *screen = new SPIScreenIO(*spi);

ST7735 *lcd = new ST7735(*screen, cs, dc);

uint8_t *buffers[2];
uint32_t palette[PALETTE_LENGTH] = {0x000000, 0xFFFFFF, 0xFF2121, 0xFF93C4, 0xFF8135, 0xFFF609,
                                    0x249CA3, 0x78DC52, 0x003FAD, 0x87F2FF, 0x8E2EC4, 0xA4839F,
                                    0x5C406C, 0xE5CDC4, 0x91463D, 0x000000};
bool updated = false;
FiberLock buffer_lock;

void fill(uint8_t color)
{
    buffer_lock.wait();

    memset(buffers[0], (color << 4) | (color & 0xF),
           ST7735_WIDTH * ST7735_HEIGHT >> 1 * sizeof(uint8_t));
    updated = true;

    buffer_lock.notify();
}

void fill_display_loop()
{
    uint8_t colour = 0;
    while (1)
    {
        fiber_sleep(RENDER_PRIORITY);
        fill(colour % 16);
        colour++;
    }
}

void swap(uint8_t **buffers)
{
    uint8_t *tmp = buffers[0];
    buffers[0] = buffers[1];
    buffers[1] = tmp;
}

void update_display()
{
    if (updated)
    {
        DMESGF("W");
        buffer_lock.wait();
        lcd->waitForSendDone();

        swap(buffers);
        lcd->sendIndexedImage(buffers[1], ST7735_WIDTH, ST7735_HEIGHT, palette);

        updated = false;
        DMESGF("N");
        buffer_lock.notify();
    }
}

void update_display_loop()
{
    while (1)
    {
        update_display();
        fiber_sleep(SCREEN_PRIORITY);
    }
}

void display_init()
{
    uBit.init();

    spi->setFrequency(15 * 10000000);
    spi->setMode(0);
    spi->write(0);

    rst.setDigitalValue(0);
    fiber_sleep(20);
    rst.setDigitalValue(1);
    fiber_sleep(20);

    lcd->init();
    lcd->setAddrWindow(0, 0, ST7735_HEIGHT, ST7735_WIDTH);
    lcd->configure(MADCTL_MV | MADCTL_MX, 0xffffff); // See function.

    // Setup double buffering and palette (need to send palette to the driver too)
    for (int i = 0; i < 2; i++)
    {
        buffers[i] = new uint8_t[ST7735_WIDTH * ST7735_HEIGHT >> 1]();
    }
    updated = true;
}
