/* Grupo G — offset constante alto alinhado | esperado: OK */
#include <stdint.h>
#include <stddef.h>
#include "verifier.h"

int main(void) {
    _Alignas(uint32_t) char buf[64];
    uint32_t *p = (uint32_t*)(buf + 48);   /* 48 = 24 * sizeof(uint16_t) -> alinhado */
    uint32_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}