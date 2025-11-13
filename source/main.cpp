#include "MicroBit.h"
#include "CodalFiber.h"

MicroBit uBit;

int main()
{
    uBit.init();

    // I2C setup:
    uBit.io.P0.setPull(PullMode::None);
    uBit.io.P1.setPull(PullMode::None);
    uBit.i2c.redirect(uBit.io.P0, uBit.io.P1);
    uBit.i2c.setFrequency(400000);

    release_fiber(); // Don't exit main
    return 1;
}
