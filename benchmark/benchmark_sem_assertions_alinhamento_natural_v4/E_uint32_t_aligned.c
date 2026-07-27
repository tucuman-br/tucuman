/* Grupo E  — offset multiplo alinhado | esperado: OK */
#include <stdint.h>
#include <stddef.h>
#include "verifier.h"

int main(void) {
   char buf[64];
    unsigned int k = VERIFIER_nondet_uint() % 6;      /* k em [0,5]: qualquer multiplo */
    uint32_t *p = (uint32_t*)(buf + k * sizeof(uint32_t));
    uint32_t z = *p;
    (void)z;
    return 0;
}
