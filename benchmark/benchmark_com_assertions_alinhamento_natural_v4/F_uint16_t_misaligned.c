#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo F — sizeof(char) desalinhado | esperado: VIOLATION */
int main(void) {
    char buf[16];
    uint16_t *p = (uint16_t*)((char*)buf + sizeof(char));
    uint16_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}
