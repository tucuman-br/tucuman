#include "verifier.h"
/* Grupo F — offset zero alinhado | esperado: OK */
int main(void) {
    _Alignas(uint16_t) char buf[16];
    uint16_t *p = (uint16_t*)((char*)buf + 0);
    return 0;
}
