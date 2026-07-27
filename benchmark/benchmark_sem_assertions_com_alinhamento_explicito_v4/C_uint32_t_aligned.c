#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo C — vetor alinhado | esperado: OK */
int main(void) {
    _Alignas(uint32_t) uint32_t vec[8];
    uint32_t *p = (uint32_t*)&vec[0];
    uint32_t z = *p;
    (void)z; 
    return 0;
}
