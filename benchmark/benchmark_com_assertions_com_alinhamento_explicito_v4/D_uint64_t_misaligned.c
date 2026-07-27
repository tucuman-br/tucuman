#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo D — ignorando offsetof (desalinhado) | esperado: VIOLATION */
struct S {
    char a;
    uint64_t b;
};

int main(void) {
    _Alignas(uint64_t) struct S s;
    char *base = (char*)&s;

    /* ignora o offsetof correto (=8) */
    uint64_t *p = (uint64_t*)(base + 1);
    uint64_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}


