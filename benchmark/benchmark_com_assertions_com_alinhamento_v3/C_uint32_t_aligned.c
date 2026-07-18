#include "verifier.h"
/* Grupo C — vetor alinhado | esperado: OK */
int main(void) {
    uint32_t vec[8];
    uint32_t *p = (uint32_t*)&vec[0];
    ALIGN_ASSERT(p);
    return 0;
}
