#include <stdint.h>

struct __attribute__((packed)) SP {
    char a;
    uint32_t b;
};

int main(void)
{
    struct SP sp;

    uint32_t *p =
        (uint32_t *)&sp.b;

    *p = 10;

    return 0;
}

