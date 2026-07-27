/* Grupo G — offset constante alto alinhado | esperado: OK */
#include <stdint.h>
#include <stddef.h>
#include "verifier.h"

int main(void) {
    char buf[64];
    uint16_t *p = (uint16_t*)(buf + 48);   /* 48 = 24 * sizeof(uint16_t) -> alinhado */
    uint16_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}