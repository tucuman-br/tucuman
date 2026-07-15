#include <stdint.h>
/* Grupo B — padding alinhado */
int main(void) {
    uint16_t x;
    uint16_t *p = (uint16_t*)((char*)&x + 0);
    (void)p; return 0;
}
