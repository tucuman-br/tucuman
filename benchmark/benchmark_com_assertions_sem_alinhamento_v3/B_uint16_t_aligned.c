#include "verifier.h"
/* Grupo B — padding alinhado | esperado: OK */
int main(void) {
    uint16_t x;
    uint16_t *p = (uint16_t*)((char*)&x + 0);
    ALIGN_ASSERT(p);
    return 0;
}
