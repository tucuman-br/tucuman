#include <stdint.h>

int main(void)
{
    char buf[8];
    uint16_t *p = (uint16_t*)((char*)buf + sizeof(char));
    uint16_t x = *p;
    (void)x;
    return 0;
}
