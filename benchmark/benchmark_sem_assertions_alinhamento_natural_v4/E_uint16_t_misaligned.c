/* Grupo E — offset multiplo desalinhado | esperado: VIOLATION */
#include <stdint.h>
#include <stddef.h>
#include "verifier.h"

int main(void) {
    char buf[64];
    unsigned int k = VERIFIER_nondet_uint() % 6;      /* qualquer multiplo, +1 sempre quebra o alinhamento */
    uint16_t *p = (uint16_t*)(buf + k * sizeof(uint16_t) + 1);
    uint16_t z = *p;
    (void)z;   
    return 0;
}
