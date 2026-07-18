#include "verifier.h"
/* Grupo B — padding desalinhado | esperado: VIOLATION */
int main(void) {
    uint32_t x;
    uint32_t *p = (uint32_t*)((char*)&x + 1);
    ALIGN_ASSERT(p);
    return 0;
}
