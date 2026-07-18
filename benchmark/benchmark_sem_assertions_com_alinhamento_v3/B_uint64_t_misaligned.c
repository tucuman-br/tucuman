#include "verifier.h"
/* Grupo B — padding desalinhado | esperado: VIOLATION */
int main(void) {
    uint64_t x;
    uint64_t *p = (uint64_t*)((char*)&x + 1);
    return 0;
}
