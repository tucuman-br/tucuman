#include "verifier.h"
/* Grupo G — offset impar desalinhado | esperado: VIOLATION */
int main(void) {
    char buf[16];
    uint16_t *p = (uint16_t*)(buf + 3);
    ALIGN_ASSERT(p);
    return 0;
}
