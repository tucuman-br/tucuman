#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo F — sizeof(char) desalinhado | esperado: VIOLATION */
int main(void) {
    char buf[16];
    uint64_t *p = (uint64_t*)((char*)buf + sizeof(char));
    uint64_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}
