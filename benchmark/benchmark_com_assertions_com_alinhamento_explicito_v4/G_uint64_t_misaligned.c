/* Grupo G — offset constante alto desalinhado | esperado: VIOLATION */
#include <stdint.h>
#include <stddef.h>
#include "verifier.h"

int main(void) {
    _Alignas(uint64_t) char buf[64];
    uint64_t *p = (uint64_t*)(buf + 49);   /* 49 = 48 + 1 -> quebra o alinhamento */
    uint64_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}
