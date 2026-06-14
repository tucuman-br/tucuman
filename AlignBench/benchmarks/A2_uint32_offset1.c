#include <stdint.h>

int main(void)
{
    char buf[8];

    uint32_t *p = (uint32_t *)(buf + 1);

    uint32_t x = *p;

    (void)x;

    return 0;
}
