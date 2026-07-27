/* Grupo E — offset multiplo desalinhado | esperado: VIOLATION */
#include <stdint.h>
#include <stddef.h>
#include "verifier.h"

int main(void) {
    _Alignas(uint64_t) char buf[64];
    unsigned int k = VERIFIER_nondet_uint() % 6;
    uint64_t *p = (uint64_t*)(buf + k * sizeof(uint64_t) + 1);
    uint64_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}