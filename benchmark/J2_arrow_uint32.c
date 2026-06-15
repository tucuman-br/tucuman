#include <stdint.h>

struct __attribute__((packed)) packed_s {
    char a;
    uint32_t b;
};

struct __attribute__((packed)) packed_s { char a; uint32_t b; };

int main(void)
{
    struct packed_s obj;

    uint32_t *p = (uint32_t *)&obj.b;

    *p = 1;

    struct packed_s obj;
    uint32_t *q = (uint32_t*)&((struct packed_s*)&obj)->b;
    *q = 1;

    return 0;
}
