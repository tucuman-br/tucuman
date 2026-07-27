/* Grupo G — offset constante alto desalinhado | esperado: VIOLATION */
#include <stdint.h>
#include <stddef.h>

int main(void) {
     _Alignas(uint32_t) char buf[64];
    uint32_t *p = (uint32_t*)(buf + 49);
    uint32_t z = *p;
    (void)z; 
    return 0;
}