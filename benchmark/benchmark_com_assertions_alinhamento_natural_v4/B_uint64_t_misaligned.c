#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo B — padding desalinhado | esperado: VIOLATION */
int main(void) {
    uint64_t x;
    uint64_t *p = (uint64_t*)((char*)&x + 1);
    uint64_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}
