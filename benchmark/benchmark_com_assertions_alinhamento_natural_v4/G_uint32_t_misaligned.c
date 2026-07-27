/* Grupo G — offset constante alto desalinhado | esperado: VIOLATION */
#include <stdint.h>
#include <stddef.h>
#include "verifier.h"

int main(void) {
    char buf[64];
    uint32_t *p = (uint32_t*)(buf + 49);   /* 49 = 48 + 1 -> quebra o alinhamento */
    uint32_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}
