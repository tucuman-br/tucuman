#include "verifier.h"
/* Grupo G — offset impar desalinhado | esperado: VIOLATION */
int main(void) {
    char buf[16];
    uint32_t *p = (uint32_t*)(buf + 5);
    ALIGN_ASSERT(p);
    return 0;
}
