#include <stdint.h>

struct __attribute__((packed)) SP {
    char a;
    uint64_t b;
};

int main(void)
{
    struct SP sp;

    uint64_t *p =
        (uint64_t *)&sp.b;

    *p = 10;

    return 0;
}
