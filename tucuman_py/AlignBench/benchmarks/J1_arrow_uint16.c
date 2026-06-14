#include <stdint.h>

struct __attribute__((packed)) packed_s {
    char a;
    uint16_t b;
};

int main(void)
{
    struct packed_s obj;

    uint16_t *p =
        (uint16_t *)&obj.b;

    *p = 1;

    return 0;
}
