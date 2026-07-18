#include "verifier.h"
/* Grupo C — vetor desalinhado | esperado: VIOLATION */
/* Grupo C — vetor (buffer de bytes) desalinhado */
int main(void) {
    char vec[32];
    uint64_t *p = (uint64_t*)&vec[9];
    uint64_t x = *p; (void)x; 
    ALIGN_ASSERT(p);
    return 0;
}
