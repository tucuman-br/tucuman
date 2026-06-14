#include <stdint.h>

int main(void)
{
    uint8_t vec[8];

    uint32_t *p =
        (uint32_t *)&vec[1];

    uint32_t x = *p;

    (void)x;

    return 0;
}
