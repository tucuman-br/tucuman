/* Grupo K — offset constante alto alinhado | esperado: OK */
#include <stdint.h>
#include <stddef.h>


int main(void) {
    char buf[64];
    uint32_t *p = (uint32_t*)(buf + 48);   /* 48 = 12 * sizeof(uint32_t) -> alinhado */
    uint32_t z = *p;
    (void)z;
    return 0;
}