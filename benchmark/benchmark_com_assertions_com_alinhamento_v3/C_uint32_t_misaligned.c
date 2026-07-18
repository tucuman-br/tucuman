#include "verifier.h"
/* Grupo C — vetor desalinhado | esperado: VIOLATION */
int main(void) {
    uint32_t vec[8];
    uint32_t *p = (uint32_t*)((char*)vec + 1);
    ALIGN_ASSERT(p);
    return 0;
}
