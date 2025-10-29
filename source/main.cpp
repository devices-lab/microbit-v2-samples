#include "display.h"

void update();
void update_loop();

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
    volatile double result = 0.0; // volatile prevents optimization

    const auto working_limit = 5000; // 50000
    for (auto i = 0; i < working_limit; ++i)
    {
        result += std::sin(i) * std::cos(i) * std::tan(i % 360);
    }
}

void update_loop()
{
    while (1)
    {
        fiber_sleep(UPDATE_PRIORITY);
        update();
    }
}
