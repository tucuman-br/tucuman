#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo C — vetor desalinhado | esperado: VIOLATION */
int main(void) {
    char vec[32];
    uint32_t *p = (uint32_t*)&vec[5];
    uint32_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}
