#include "verifier.h"
/* Grupo G — offset multiplo alinhado | esperado: OK */
int main(void) {
    char buf[16];
    uint64_t *p = (uint64_t*)(buf + 8);
    ALIGN_ASSERT(p);
    return 0;
}
