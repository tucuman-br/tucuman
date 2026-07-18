#include "verifier.h"
/* Grupo A — offset constante desalinhado | esperado: VIOLATION */
int main(void) {
    char buf[16];
    uint16_t *p = (uint16_t*)(buf + 1);
    ALIGN_ASSERT(P);
    return 0;
}
