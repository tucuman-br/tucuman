#include <stdint.h>

struct S { char a; uint64_t b; };

int main(void)
{
    struct S sp;
    uint64_t *p = (uint64_t*)&sp.b;
    *p = 10;
    return 0;
}
