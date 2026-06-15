#include <stdint.h>

int main(void)
{
    char buf[4];
    uint64_t *p = (uint64_t*)(buf + 1);
    uint64_t x = *p;
    (void)x;
    return 0;
}
