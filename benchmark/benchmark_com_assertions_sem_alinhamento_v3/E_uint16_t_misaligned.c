#include "verifier.h"
/* Grupo E — offset simbolico desalinhado | esperado: VIOLATION */
int main(void) {
    char buf[16];
    unsigned int i = VERIFIER_nondet_uint();
    uint16_t *p = (uint16_t*)(buf + i);
    ALIGN_ASSERT(p);
    return 0;
}
