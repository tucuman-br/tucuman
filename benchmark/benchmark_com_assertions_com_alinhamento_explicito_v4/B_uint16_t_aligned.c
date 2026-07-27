#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo B — padding alinhado | esperado: OK */
int main(void) {
    _Alignas(uint16_t) uint16_t x;
    uint16_t *p = (uint16_t*)((char*)&x + 0);
    uint16_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}
