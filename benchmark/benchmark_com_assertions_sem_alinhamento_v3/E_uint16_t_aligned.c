#include "verifier.h"
/* Grupo E — offset constante alinhado | esperado: OK */
int main(void) {
    char buf[16];
    uint16_t *p = (uint16_t*)(buf + 2);
    ALIGN_ASSERT(p);
    return 0;
}
