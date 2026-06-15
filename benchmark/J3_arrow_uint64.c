#include <stdint.h>

struct __attribute__((packed)) packed_s {
    char a;
    uint64_t b;
};

struct __attribute__((packed)) packed_s { char a; uint64_t b; };

int main(void)
{
    struct packed_s obj;

    uint64_t *p = (uint64_t *)&obj.b;

    *p = 1;


    struct packed_s obj;
    uint64_t *q = (uint64_t*)&((struct packed_s*)&obj)->b;
    *q = 1;

    return 0;
}
