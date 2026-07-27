/* Grupo G — offset constante alto alinhado | esperado: OK */
#include <stdint.h>
#include <stddef.h>

int main(void) {
     _Alignas(uint64_t) char buf[64];
    uint64_t *p = (uint64_t*)(buf + 48);
    uint64_t z = *p;
    (void)z; 
    return 0;
}


