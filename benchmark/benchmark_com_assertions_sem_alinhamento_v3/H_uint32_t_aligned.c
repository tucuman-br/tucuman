#include "verifier.h"
/* Grupo H — acesso packed alinhado (sp) | esperado: OK */
struct S { char a; uint32_t b; };
int main(void) {
    struct S sp;
    uint32_t *p = (uint32_t*)&sp.b;
    ALIGN_ASSERT(p);
    return 0;
}
