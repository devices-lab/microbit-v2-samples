#include "MicroBit.h"
#include "math.h"

// Page 60
// https://www.lcsc.com/datasheet/C126672.pdf

extern MicroBit uBit;

// Where this appears elsewhere in the code, use the datasheet
// to work out what values should be used.
#define LOOK_AT_THE_DATASHEET NULL

//------------------------------------------------------------
// Registers for configuration, and the values to set them to:
//------------------------------------------------------------

#define LSM6DSL_ADDR LOOK_AT_THE_DATASHEET // Make sure the address is in the top 7 bits because the R/W bit in the LSbit.

#define LSM6DSL_CTRL1_XL_REG 0x10
#define LSM6DSL_CTRL1_XL_CFG LOOK_AT_THE_DATASHEET // ODR_XL1, ODR_XL0 for 52Hz

#define LSM6DSL_CTRL2_G_REG LOOK_AT_THE_DATASHEET
#define LSM6DSL_CTRL2_G_CFG LOOK_AT_THE_DATASHEET // ODR_G1, ODR_G0 for 52Hz

#define LSM6DSL_CTRL3_C_REG LOOK_AT_THE_DATASHEET
#define LSM6DSL_CTRL3_C_CFG ((1 << 6) | (1 << 2)) // BDU, IF_INC

//-----------------------------
// Registers to read data from:
//-----------------------------

#define LSM6DSL_OUT_X_L_G 0x22
#define LSM6DSL_OUT_Y_L_G LOOK_AT_THE_DATASHEET
#define LSM6DSL_OUT_Z_L_G LOOK_AT_THE_DATASHEET

#define LSM6DSL_OUT_X_L_A 0x28
#define LSM6DSL_OUT_Y_L_A LOOK_AT_THE_DATASHEET
#define LSM6DSL_OUT_Z_L_A LOOK_AT_THE_DATASHEET

//--------------------------------------------------------
// HELPER FUNCTIONS
// These are written for you & do not need to be changed:
//--------------------------------------------------------


// Only the first param is neccessary if you multi-byte read
static int16_t readFromRegisterI16(uint8_t reg1)
{
    // Alternatively do a multi-byte read:
    uint8_t values[2];
    uBit.i2c.readRegister(LSM6DSL_ADDR, reg1, values, 2);

    int16_t result = (values[1] << 8) | values[0];
    result = result >> 6;
    return result;
}

/**
 * Helper function for LSM6DSL_init.
 */
static void writeToRegister(uint8_t reg, uint8_t value)
{
    uint8_t data[] = {reg, value};
    uBit.i2c.write(LSM6DSL_ADDR, data, 2);
}

//-----------------------------
// EXPORTED FUNCTIONS:
// These are completed for you:
//-----------------------------

static bool isInit = false;
void LSM6DSL_init()
{
    if (isInit)
        return;

    writeToRegister(LSM6DSL_CTRL1_XL_REG, LSM6DSL_CTRL1_XL_CFG);
    writeToRegister(LSM6DSL_CTRL2_G_REG, LSM6DSL_CTRL2_G_CFG);
    writeToRegister(LSM6DSL_CTRL3_C_REG, LSM6DSL_CTRL3_C_CFG);

    uBit.sleep(20); // This is required for first read to not be all zeroes.
    isInit = true;
}


int16_t LSM6DSL_acceleration_X()
{
    return readFromRegisterI16(LSM6DSL_OUT_X_L_A);
}

int16_t LSM6DSL_acceleration_Y() {
    return readFromRegisterI16(LSM6DSL_OUT_Y_L_A);
}

int16_t LSM6DSL_acceleration_Z() {
    return readFromRegisterI16(LSM6DSL_OUT_Z_L_A);
}

int16_t LSM6DSL_gyro_X() {
    return readFromRegisterI16(LSM6DSL_OUT_X_L_G);
}

int16_t LSM6DSL_gyro_Y() {
    return readFromRegisterI16(LSM6DSL_OUT_Y_L_G);
}

int16_t LSM6DSL_gyro_Z() {
    return readFromRegisterI16(LSM6DSL_OUT_Z_L_G);
}
