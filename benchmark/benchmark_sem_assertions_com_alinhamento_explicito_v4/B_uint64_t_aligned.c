#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo B — padding alinhado | esperado: OK */
int main(void) {
    _Alignas(uint64_t) uint64_t x;
    uint64_t *p = (uint64_t*)((char*)&x + 0);
    uint64_t z = *p;
    (void)z; 
    return 0;
}
