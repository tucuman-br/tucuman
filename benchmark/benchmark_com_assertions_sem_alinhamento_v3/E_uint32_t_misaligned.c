#include "verifier.h"
/* Grupo E — offset simbolico desalinhado | esperado: VIOLATION */
int main(void) {
    char buf[16];
    unsigned int i = VERIFIER_nondet_uint();
    uint32_t *p = (uint32_t*)(buf + i);
    ALIGN_ASSERT(p);
    return 0;
}
