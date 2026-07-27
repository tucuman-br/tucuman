#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo A — offset constante alinhado | esperado: OK */
int main(void) {
    _Alignas(uint32_t) char buf[16];
    uint32_t *p = (uint32_t*)(buf + 0);
    uint32_t z = *p;
    (void)z; 
    return 0;
}
