#include <stdint.h>

unsigned nondet_uint(void);

int main(void)
{
    char buf[16];

    unsigned i = nondet_uint();

    __CPROVER_assume(i < 8);

    uint32_t *p =
        (uint32_t *)(buf + i);

    uint32_t x = *p;

    (void)x;

    return 0;
}
