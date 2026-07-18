#include "verifier.h"
/* Grupo E — offset constante alinhado | esperado: OK */
int main(void) {
     _Alignas(uint16_t) char buf[16];
    uint16_t *p = (uint16_t*)(buf + 2);
    return 0;
}
