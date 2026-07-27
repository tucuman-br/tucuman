#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo B — padding desalinhado | esperado: VIOLATION */
int main(void) {
    _Alignas(uint16_t) uint16_t x;
    uint16_t *p = (uint16_t*)((char*)&x + 1);
    uint16_t z = *p;
    (void)z; 
    return 0;
}
