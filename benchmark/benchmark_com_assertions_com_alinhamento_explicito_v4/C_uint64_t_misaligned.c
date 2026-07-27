#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo C — vetor desalinhado | esperado: VIOLATION */
int main(void) {
    _Alignas(uint32_t)  uint64_t vec[8];
    uint64_t *p = (uint64_t*)((char*)vec + 1);
    uint64_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}
