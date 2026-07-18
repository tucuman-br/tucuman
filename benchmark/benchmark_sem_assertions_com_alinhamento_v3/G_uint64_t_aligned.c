#include "verifier.h"
/* Grupo G — offset multiplo alinhado | esperado: OK */
int main(void) {
     _Alignas(uint64_t) char buf[16];
    uint64_t *p = (uint64_t*)(buf + 8);
    return 0;
}
