#include "verifier.h"
/* Grupo C — vetor desalinhado | esperado: VIOLATION */
/* Grupo C — vetor (buffer de bytes) desalinhado */
int main(void) {
    char vec[32];
    uint16_t *p = (uint16_t*)&vec[3];
    uint16_t x = *p; (void)x; 
    ALIGN_ASSERT(p);
    return 0;

}
