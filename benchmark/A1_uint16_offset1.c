#include <stdint.h>

int main(void)
{
    char buf[4];
    uint16_t *p = (uint16_t*)(buf + 1);
    uint16_t x = *p;
    (void)x;
    return 0;
}
