/* Grupo G — offset constante alto desalinhado | esperado: VIOLATION */
#include <stdint.h>
#include <stddef.h>

int main(void) {
     _Alignas(uint64_t) char buf[64];
    uint64_t *p = (uint64_t*)(buf + 49);
    uint64_t z = *p;
    (void)z; 
    return 0;
}


