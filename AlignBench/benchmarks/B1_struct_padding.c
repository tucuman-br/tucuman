#include <stdint.h>

struct S {
    char a;
    uint16_t b;
};

int main(void)
{
    struct S s;

    char *base = (char *)&s;

    /* offset incorreto */
    uint16_t *pb =
        (uint16_t *)(base + 1);

    *pb = 0xFFFF;

    return 0;
}
