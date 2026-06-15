#include <stdint.h>

struct S { char a; uint32_t b; };

int main(void)
{
    struct S s;
    char *base = (char*)&s;
    uint32_t *pb = (uint32_t*)(base + 1);
    *pb = 0xFFFF;
    return 0;
}
