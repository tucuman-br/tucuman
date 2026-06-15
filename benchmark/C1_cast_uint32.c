#include <stdint.h>

int main(void)
{
    uint32_t x;
    uint16_t *p = (uint16_t*)((char*)&x + 1);
    *p = 123;
    return 0;
}
