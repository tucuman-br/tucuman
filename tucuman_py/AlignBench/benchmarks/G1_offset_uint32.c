#include <stdint.h>

int main(void)
{
    char buf[16];

    uint32_t *p =
        (uint32_t *)(buf + 5);

    uint32_t x = *p;

    (void)x;

    return 0;
}
