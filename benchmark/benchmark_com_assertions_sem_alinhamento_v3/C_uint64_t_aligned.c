#include "verifier.h"
/* Grupo C — vetor alinhado | esperado: OK */
int main(void) {
    uint64_t vec[8];
    uint64_t *p = (uint64_t*)&vec[0];
    ALIGN_ASSERT(p);
    return 0;
}
