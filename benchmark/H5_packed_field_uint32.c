#include <stdint.h>

struct S { char a; uint32_t b; };

int main(void)
{
    struct S sp;
    uint32_t *p = (uint32_t*)&sp.b;
    *p = 10;
    return 0;
}
