/* Grupo G — offset constante alto alinhado | esperado: OK */
#include <stdint.h>
#include <stddef.h>

int main(void) {
    char buf[64];
    uint64_t *p = (uint64_t*)(buf + 48);   /* 48 = 6 * sizeof(uint64_t) -> alinhado */
    uint64_t z = *p;
    (void)z;
    return 0;
}