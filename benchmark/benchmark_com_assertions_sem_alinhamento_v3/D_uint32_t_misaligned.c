#include "verifier.h"
/* Grupo D — ignorando offsetof (desalinhado) | esperado: VIOLATION */
int main(void) {
    char buf[16];
    uint32_t *p = (uint32_t*)(buf + 1);
    ALIGN_ASSERT(p);
    return 0;
}
