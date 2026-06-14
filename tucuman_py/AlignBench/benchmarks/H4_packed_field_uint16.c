#include <stdint.h>

struct __attribute__((packed)) SP {
    char a;
    uint16_t b;
};

int main(void)
{
    struct SP sp;

    uint16_t *p =
        (uint16_t *)&sp.b;

    *p = 10;

    return 0;
}
