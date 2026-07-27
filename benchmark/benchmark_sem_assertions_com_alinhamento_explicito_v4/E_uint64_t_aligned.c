/* Grupo E  — offset multiplo alinhado | esperado: OK */
#include <stdint.h>
#include <stddef.h>
#include "verifier.h"

int main(void) {
    _Alignas(uint16_t) char buf[64];
    unsigned int k = VERIFIER_nondet_uint() % 6;      /* k em [0,5]: qualquer multiplo */
    uint64_t *p = (uint64_t*)(buf + k * sizeof(uint64_t));
    uint64_t z = *p;
    (void)z;
    return 0;
}