#include "verifier.h"
/* Grupo H — acesso packed alinhado (sp) | esperado: OK */
struct S { char a; uint16_t b; };
int main(void) {
    struct S sp;
    uint16_t *p = (uint16_t*)&sp.b;
    return 0;
}
