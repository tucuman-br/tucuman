#include "verifier.h"
/* Grupo A — offset constante desalinhado | esperado: VIOLATION */
int main(void) {
    _Alignas(uint16_t) char buf[16];
    uint16_t *p = (uint16_t*)(buf + 1);    
    return 0;
}
