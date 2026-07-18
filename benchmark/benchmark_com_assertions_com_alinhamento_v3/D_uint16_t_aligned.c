#include "verifier.h"
/* Grupo D — com offsetof (alinhado) | esperado: OK */
struct S { char a; uint16_t b; };
int main(void) {
    struct S s;
    char *base = (char*)&s;
    uint16_t *p = (uint16_t*)(base + offsetof(struct S, b));
    ALIGN_ASSERT(p);
    return 0;
}
