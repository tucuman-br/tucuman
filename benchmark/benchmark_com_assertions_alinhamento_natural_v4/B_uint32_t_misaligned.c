#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo B — padding desalinhado | esperado: VIOLATION */
int main(void) {
    uint32_t x;
    uint32_t *p = (uint32_t*)((char*)&x + 1);
    uint32_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}
