#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo A — offset constante desalinhado | esperado: VIOLATION */
int main(void) {
    char buf[16];
    uint16_t *p = (uint16_t*)(buf + 1);
    uint16_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}
