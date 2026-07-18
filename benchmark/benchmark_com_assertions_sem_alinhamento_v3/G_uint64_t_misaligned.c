#include "verifier.h"
/* Grupo G — offset impar desalinhado | esperado: VIOLATION */
int main(void) {
    char buf[16];
    uint64_t *p = (uint64_t*)(buf + 7);
    ALIGN_ASSERT(p);
    return 0;
}
