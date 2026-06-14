#include <stdint.h>

unsigned nondet_uint(void);

int main(void)
{
    char buf[16];

    unsigned i = nondet_uint();

    __CPROVER_assume(i < 8);

    uint32_t *p =
        (uint32_t *)(buf + i);

    __CPROVER_assert(
        ((uintptr_t)p % 4) == 0,
        "pointer must be aligned");

    return 0;
}
