/* Grupo G — offset constante alto desalinhado | esperado: VIOLATION */
#include <stdint.h>
#include <stddef.h>

int main(void) {
    char buf[64];
    uint32_t *p = (uint32_t*)(buf + 49);   /* 49 nao e multiplo de 4 -> desalinhado */
    uint32_t z = *p;
    (void)z;
    return 0;
}