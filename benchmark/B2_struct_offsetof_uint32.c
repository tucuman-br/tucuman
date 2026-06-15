#include <stdint.h>
#include <stddef.h>

struct S { char a; uint32_t b; };

int main(void)
{
    struct S s;
    char *base = (char*)&s;
    uint32_t *pb = (uint32_t*)(base + offsetof(struct S, b));
    *pb = 0xFFFF;
    return 0;
}
