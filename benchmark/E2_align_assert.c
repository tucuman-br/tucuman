#include <stdint.h>

unsigned nondet_uint(void);

int main(void)
{
    char buf[16];
    unsigned i = nondet_uint();
    uint32_t *p = (uint32_t*)(buf + i);
    return 0;
}
