#include "verifier.h"
/* Grupo E — offset constante alinhado | esperado: OK */
int main(void) {
    char buf[16];
    uint32_t *p = (uint32_t*)(buf + 4);
    ALIGN_ASSERT(p);
    return 0;
}
