/* Grupo G — offset constante alto alinhado | esperado: OK */
#include <stdint.h>
#include <stddef.h>
#include "verifier.h"

int main(void) {
    char buf[64];
    uint64_t *p = (uint64_t*)(buf + 48);   /* 48 = 24 * sizeof(uint16_t) -> alinhado */
    uint64_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}