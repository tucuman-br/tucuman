#include <stdint.h>

struct S { char a; uint16_t b; };

int main(void)
{
    struct S sp;
    uint16_t *p = (uint16_t*)&sp.b;
    *p = 10;
    return 0;
}
