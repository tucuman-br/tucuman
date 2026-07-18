#include "verifier.h"
/* Grupo A — offset constante alinhado | esperado: OK */
int main(void) {
    char buf[16];
    uint16_t *p = (uint16_t*)(buf + 0);
    ALIGN_ASSERT(P);
    return 0;
}
