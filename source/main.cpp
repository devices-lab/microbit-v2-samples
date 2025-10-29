#include "display.h"

void update();
void update_loop();
void calculate_expensive_value();
volatile double *memory_expensive_fn();

int main()
{
    display_init();

    create_fiber(update_display_loop);
    create_fiber(fill_display_loop);
    create_fiber(update_loop);

    while (1)
    {
        fiber_sleep(3);
    }
}

void update()
{
    // calculate_expensive_value();
}

/**
 * Arbitrary code designed to simulate an expensive calculation.
 * Run by multiple threads at once.
 */
void calculate_expensive_value()
{
    volatile double *arbitrary_filled_array = memory_expensive_fn();

    volatile double dst = 0.0;
    const auto working_limit = 10; // 25
    for (auto i = 0; i < working_limit; ++i)
    {
        dst += std::sin(i) * std::cos(i) * std::tan(i % 360) + arbitrary_filled_array[i];
    }
    dst /= 3.3;
    free(const_cast<double *>(arbitrary_filled_array));
}


/**
* Allocate a 2 large arrays, fill them, copy to each other, free, etc.
* Called by calculate_expensive_value above.
*/
volatile double *memory_expensive_fn()
{
    // const size_t nums = 800;
    const size_t nums = 1000;
    volatile double *src = static_cast<volatile double *>(malloc(nums * sizeof(double)));

    for (size_t i = 0; i < nums; i++)
        src[i] = 0.0;

    for (size_t i = 0; i < nums; i += 2)
    {
        *src = i * 3.3;
    }

    volatile double *dst = static_cast<volatile double *>(malloc(nums * sizeof(double)));
    memcpy(const_cast<double *>(dst), const_cast<double*>(src), nums * sizeof(double));

    free(const_cast<double *>(src));
    return dst;
}

void update_loop()
{
    const size_t num_fibers_calculating_expensive_value = 8; // 6 should prevent hanging
    while (1)
    {
        fiber_sleep(UPDATE_PRIORITY);
        for (size_t i = 0; i < num_fibers_calculating_expensive_value; i++)
        {
            create_fiber(calculate_expensive_value);
        }
    }
}
