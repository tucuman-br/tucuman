#include "verifier.h"
/* Grupo H — acesso packed alinhado (sp) | esperado: OK */
struct S { char a; uint64_t b; };
int main(void) {
    struct S sp;
    uint64_t *p = (uint64_t*)&sp.b;
    return 0;
}
