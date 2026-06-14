#include <stdint.h>

int main(void)
{
    char buf[16];

    uint64_t *p =
        (uint64_t *)((void *)buf + 1);

    *p = 10;

    return 0;
}
