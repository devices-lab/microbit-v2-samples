#include "MicroBit.h"
#include "SSD1306.h"

MicroBit uBit;

int main()
{
    uBit.init();
    uBit.display.scroll("Hi :)");
}
