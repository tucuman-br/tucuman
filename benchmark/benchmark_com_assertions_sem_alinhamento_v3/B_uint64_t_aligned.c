#include "verifier.h"
/* Grupo B — padding alinhado | esperado: OK */
int main(void) {
    uint64_t x;
    uint64_t *p = (uint64_t*)((char*)&x + 0);
    ALIGN_ASSERT(p);
    return 0;
}
