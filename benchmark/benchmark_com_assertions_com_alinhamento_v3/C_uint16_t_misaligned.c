#include "verifier.h"
/* Grupo C — vetor desalinhado | esperado: VIOLATION */
int main(void) {
    uint16_t vec[8];
    uint16_t *p = (uint16_t*)((char*)vec + 1);
    ALIGN_ASSERT(p);
    return 0;
}
