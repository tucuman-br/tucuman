#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo C — vetor alinhado | esperado: OK */
int main(void) {
    _Alignas(uint16_t) uint16_t vec[8];
    uint16_t *p = (uint16_t*)&vec[0];
    uint16_t z = *p;
    (void)z; 
    return 0;
}
