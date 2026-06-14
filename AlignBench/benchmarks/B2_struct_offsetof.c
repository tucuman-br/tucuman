#include <stdint.h>
#include <stddef.h>

struct S {
    char a;
    uint16_t b;
};

int main(void)
{
    struct S s;

    char *base = (char *)&s;

    uint16_t *pb =
        (uint16_t *)(base +
        offsetof(struct S,b));

    *pb = 0xFFFF;

    return 0;
}
