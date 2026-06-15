#include <stdint.h>

struct S { char a; uint16_t b; };

int main(void)
{
    struct S s;
    uint16_t *p = (uint16_t*)&s.b;
    *p = 10;
    return 0;
}
