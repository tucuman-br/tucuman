#include <stdint.h>

int main(void)
{
    char buf[8];

    uint32_t *p =
        (uint32_t *)((void *)buf + 1);

    *p = 10;

    return 0;
}
