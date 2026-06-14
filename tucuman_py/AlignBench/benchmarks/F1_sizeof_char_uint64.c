#include <stdint.h>

int main(void)
{
    char buf[16];

    uint64_t *p =
        (uint64_t *)(buf + sizeof(char));

    uint64_t x = *p;

    (void)x;

    return 0;
}
