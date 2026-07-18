#include "verifier.h"
/* Grupo G — offset impar desalinhado | esperado: VIOLATION */
int main(void) {
    _Alignas(uint16_t) char buf[16];
    uint16_t *p = (uint16_t*)(buf + 3);
    return 0;
}
