#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo A — offset constante alinhado | esperado: OK */
int main(void) {
    char buf[16];
    uint64_t *p = (uint64_t*)(buf + 0);
    uint64_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}
