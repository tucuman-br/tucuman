#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo C — vetor desalinhado | esperado: VIOLATION */
int main(void) {
    _Alignas(uint32_t) uint32_t vec[8];
    uint32_t *p = (uint32_t*)((char*)vec + 1);
    uint32_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}
