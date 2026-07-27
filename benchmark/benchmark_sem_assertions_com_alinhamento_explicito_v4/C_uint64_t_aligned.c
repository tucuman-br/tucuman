#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo C — vetor alinhado | esperado: OK */
int main(void) {
    _Alignas(uint64_t) uint64_t vec[8];
    uint64_t *p = (uint64_t*)&vec[0];
    uint64_t z = *p;
    (void)z; 
    return 0;
}
