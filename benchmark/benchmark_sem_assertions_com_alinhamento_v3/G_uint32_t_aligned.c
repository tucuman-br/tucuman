#include "verifier.h"
/* Grupo G — offset multiplo alinhado | esperado: OK */
int main(void) {
     _Alignas(uint32_t)char buf[16];
    uint32_t *p = (uint32_t*)(buf + 4);
    return 0;
}
