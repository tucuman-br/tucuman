#include "verifier.h"
/* Grupo D — com offsetof (alinhado) | esperado: OK */
struct S { char a; uint32_t b; };
int main(void) {
    struct S s;
    char *base = (char*)&s;
    uint32_t *p = (uint32_t*)(base + offsetof(struct S, b));
    ALIGN_ASSERT(p);
    return 0;
}
