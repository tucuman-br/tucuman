#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo D — ignorando offsetof (desalinhado) | esperado: VIOLATION */
struct S {
    char a;
    uint32_t b;
};

int main(void) {
    _Alignas(uint32_t) struct S s;
    char *base = (char*)&s;

    /* ignora o offsetof correto (=8) */
    uint32_t *p = (uint32_t*)(base + 1);
    uint32_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}
