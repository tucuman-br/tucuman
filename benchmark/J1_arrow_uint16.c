#include <stdint.h>

struct __attribute__((packed)) packed_s {
    char a;
    uint16_t b;
};

struct __attribute__((packed)) packed_s { char a; uint16_t b; };

int main(void)
{
    struct packed_s obj;
    uint16_t *p = (uint16_t*)&((struct packed_s*)&obj)->b;
    *p = 1;

int main(void)
{
    struct packed_s obj;

    uint16_t *p = (uint16_t *)&obj.b;

    *p = 1;


    struct packed_s obj;
    uint16_t *q = (uint16_t*)&((struct packed_s*)&obj)->b;
    *q = 1;

    return 0;
}
