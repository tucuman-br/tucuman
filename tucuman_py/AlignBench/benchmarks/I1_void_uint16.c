#include <stdint.h>

int main(void)
{
    char buf[8];

    uint16_t *p =
        (uint16_t *)((void *)buf + 1);

    *p = 10;

    return 0;
}
