#include <stdint.h>

int main(void)
{
    char buf[8];

    uint16_t *p =
        (uint16_t *)(buf + 3);

    uint16_t x = *p;

    (void)x;

    return 0;
}
