#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo F — sizeof(char) desalinhado | esperado: VIOLATION */
int main(void) {
    _Alignas(uint32_t) char buf[16];
    uint32_t *p = (uint32_t*)((char*)buf + sizeof(char));
    uint32_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}

