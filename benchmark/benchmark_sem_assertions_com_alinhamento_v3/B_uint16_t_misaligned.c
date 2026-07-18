#include "verifier.h"
/* Grupo B — padding desalinhado | esperado: VIOLATION */
int main(void) {
    uint16_t x;
    uint16_t *p = (uint16_t*)((char*)&x + 1);
    return 0;
}
