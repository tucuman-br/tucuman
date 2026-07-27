/* Grupo G — offset constante alto desalinhado | esperado: VIOLATION */
#include <stdint.h>
#include <stddef.h>

int main(void) {
 char buf[64];
    uint16_t *p = (uint16_t*)(buf + 49);   /* 49 = 48 + 1 -> quebra o alinhamento */
    uint16_t z = *p;
    (void)z;
    return 0;
}