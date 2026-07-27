/* Grupo E — offset multiplo desalinhado | esperado: VIOLATION */
#include <stdint.h>
#include <stddef.h>
#include "verifier.h"

int main(void) {
    char buf[64];
    unsigned int k = VERIFIER_nondet_uint() % 6;      /* qualquer multiplo, +1 sempre quebra o alinhamento */
    uint32_t *p = (uint32_t*)(buf + k * sizeof(uint32_t) + 1);
    uint32_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}