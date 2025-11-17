#include "MicroBit.h"
#include "math.h"

// Datasheet: Pages 13, 21, 25, 26 are particularly noteworthy.
// https://www.ti.com/lit/ds/symlink/tmp117.pdf?ts=1762983724704

extern MicroBit uBit;

// Where this appears elsewhere in the code, use the datasheet
// to work out what values should be used.
#define LOOK_AT_THE_DATASHEET NULL

// registers:

#define TMP117_ADDR LOOK_AT_THE_DATASHEET // Make sure the address is in the top 7 bits because the R/W bit in the LSbit.
#define TMP117_TEMP_DATA_REG LOOK_AT_THE_DATASHEET

// See page 13: 7.3.3:
// Scalar to convert from LSB value to degrees C
#define TMP117_RESOLUTION 0.0078125f

/**
 * We get two uint8_t which we can concatenate and then scale using TMP117_RESOLUTION
 * Read page 13: 7.3.3 for more info.
 */
float TMP117_temperature()
{
    uint8_t temp[2];
    uBit.i2c.readRegister(TMP117_ADDR, TMP117_TEMP_DATA_REG, temp, 2);
    int16_t result = ((temp[0] << 8) | temp[1]);
    return static_cast<float>(result) * TMP117_RESOLUTION;
}
