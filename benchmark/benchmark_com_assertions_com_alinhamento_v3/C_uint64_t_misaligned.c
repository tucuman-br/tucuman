#include "verifier.h"
/* Grupo C — vetor desalinhado | esperado: VIOLATION */
int main(void) {
    uint64_t vec[8];
    uint64_t *p = (uint64_t*)((char*)vec + 1);
    ALIGN_ASSERT(p);
    return 0;
}
