#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo C — vetor desalinhado | esperado: VIOLATION */
int main(void) {
    _Alignas(uint16_t) uint16_t vec[8];
    uint16_t *p = (uint16_t*)((char*)vec + 1);
    uint16_t z = *p;
    (void)z; 
    return 0;
}
