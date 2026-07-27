/* Grupo G — offset constante alto desalinhado | esperado: VIOLATION */
#include <stdint.h>
#include <stddef.h>

int main(void) {
     _Alignas(uint16_t) char buf[64];
    uint16_t *p = (uint16_t*)(buf + 49);
    uint16_t z = *p;
    (void)z; 
    return 0;
}