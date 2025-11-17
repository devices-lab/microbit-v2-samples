#include "MicroBit.h"
#include "SSD1306.h"

MicroBit uBit;

// Exported function from TMP117.cpp; these are implemented for you
// you need to find and replace LOOK_AT_THE_DATASHEET to get it working:
extern float TMP117_temperature();

// Exported functions from LSM6DSL.cpp; these are implemented for you
// you need to find and replace LOOK_AT_THE_DATASHEET to get it working:
extern void LSM6DSL_init();
extern int16_t LSM6DSL_acceleration_X();
extern int16_t LSM6DSL_acceleration_Y();
extern int16_t LSM6DSL_acceleration_Z();
extern int16_t LSM6DSL_gyro_X();
extern int16_t LSM6DSL_gyro_Y();
extern int16_t LSM6DSL_gyro_Z();

// We are using +-2g range (this sensor's default). 
// This is the minimum and maximum acceleration it can return.
// This might be useful for normalisation in Task 3.
#define LSM6DSL_2G_MIN_ACC -512
#define LSM6DSL_2G_MAX_ACC 511

#define WAIT_PERIOD_US 20000 // main function loop period.

/**
 * Setup the I2C devices ready for the tasks
 * See main()
 */
void i2c_devices_init()
{
    // I2C setup:
    uBit.i2c.redirect(uBit.io.P0, uBit.io.P1);
    uBit.i2c.setFrequency(400000);

    // For task 2, 3 and 4:
    LSM6DSL_init();

    // For task 3:
    SSD1306_init();
    // Clear the screen:
    for (unsigned col = 0; col < OLED_WIDTH; col++)
        SSD1306_clearColumn(col);
}

int main()
{
    uBit.init();
    i2c_devices_init();
    uint8_t num_loops = 0;
    uint8_t col = 0; // Useful for Task 3
    
    // Uncomment for Task 4: Wait for btn A press before running:
    // while (!uBit.buttonA.isPressed())
    //     ;
    // uBit.display.printChar('A');

    // Uncomment for Task 4: Setup the datalogger:
    // uBit.log.clear(true);
    // uBit.log.setTimeStamp(TimeStampFormat::None);
    // uBit.log.setVisibility(true); // Required to get MY_DATA.HTML off microbit.
    

    while (1) {
        // Task 1: print the TMP117's temperature reading over serial:
        // This prints 0 until you have fixed the LOOK_AT_THE_DATASHEET issues inside TMP117.cpp
        float temperature = TMP117_temperature();
        uBit.serial.printf("t: %d\r\n", (int) temperature);

        // Task 2: print all 6 axes of the LSM over serial:
        // The first axis is provided but this code will just
        // print 0 and/or won't change as you move it until you have
        // fixed the LOOK_AT_THE_DATASHEET issues in LSM6DSL.cpp
        //
        // Uncomment for Task 2:
        //---------------------------------------
        // int16_t ax = LSM6DSL_acceleration_X();
        // uBit.serial.printf("ax: %d\r\n", ax);
        //---------------------------------------

        // Task 3: Draw the X axis LSM data as a pixel on the y-axis of the OLED
        // Look at the SSD1306.h file to see what the OLED can do.

        // Task 4: Use logData to store your 7 sensor readings using these column names:
        // "t", "a-x", "a-y", "a-z", "g-x", "g-y", "g-z"
        //
        // Uncomment for Task 4:
        //-------------------------------------------------------------------
        // uBit.log.beginRow();
        //// Log 7 sensor readings here, they should all appear on the same row.
        // uBit.log.endRow();
        //-------------------------------------------------------------------


        // Toggling P2 each time around the loop allows us to check how long a loop takes using an oscilloscope.
        uBit.io.P2.setDigitalValue(num_loops & 1);
        num_loops++;

        // Sleep for 20ms with the aim of logging a new set of data every 20ms.
        // For task 5, try to make the logging period more accurate; sleeping for 20ms might not be accurate.
        // Look into using system_timer_current_time_us().
        uBit.sleep(20);
    }
    return 1;
}
