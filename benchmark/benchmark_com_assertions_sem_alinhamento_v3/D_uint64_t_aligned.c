#include "verifier.h"
/* Grupo D — com offsetof (alinhado) | esperado: OK */
struct S { char a; uint64_t b; };
int main(void) {
    struct S s;
    char *base = (char*)&s;
    uint64_t *p = (uint64_t*)(base + offsetof(struct S, b));
    ALIGN_ASSERT(p);
    return 0;
}
