#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo A — offset constante desalinhado | esperado: VIOLATION */
int main(void) {
    _Alignas(uint32_t) char buf[16];
    uint32_t *p = (uint32_t*)(buf + 1);
    uint32_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}
