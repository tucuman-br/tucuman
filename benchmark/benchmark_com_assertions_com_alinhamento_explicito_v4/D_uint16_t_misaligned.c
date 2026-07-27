#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo D — ignorando offsetof (desalinhado) | esperado: VIOLATION */
struct S {
    char a;
    uint16_t b;
};

int main(void) {
    _Alignas(uint16_t) struct S s;
    char *base = (char*)&s;

    /* ignora o offsetof correto (=8) */
    uint16_t *p = (uint16_t*)(base + 1);
    uint16_t z = *p;
    (void)z;

    ALIGN_ASSERT(p);
    return 0;
}
