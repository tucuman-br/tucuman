#include <stdint.h>

struct S { char a; uint64_t b; };

int main(void)
{
    struct S s;
    uint64_t *p = (uint64_t*)&s.b;
    *p = 10;
    return 0;
}
