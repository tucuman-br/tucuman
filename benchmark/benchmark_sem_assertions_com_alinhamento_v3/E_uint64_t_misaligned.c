#include "verifier.h"
/* Grupo E — offset simbolico desalinhado | esperado: VIOLATION */
int main(void) {
     _Alignas(uint64_t) char buf[16];
    unsigned int i = VERIFIER_nondet_uint();
    uint64_t *p = (uint64_t*)(buf + i);
    return 0;
}
