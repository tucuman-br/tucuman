/* Grupo E  — offset multiplo alinhado | esperado: OK */
#include <stdint.h>
#include <stddef.h>
#include "verifier.h"

int main(void) {
    char buf[64];
    unsigned int k = VERIFIER_nondet_uint() % 6;      /* k em [0,5]: qualquer multiplo */
    uint16_t *p = (uint16_t*)(buf + k * sizeof(uint16_t));
    uint16_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}