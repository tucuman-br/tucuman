#include "verifier.h"
/* Grupo D — ignorando offsetof (desalinhado) | esperado: VIOLATION */
struct S {
    char a;
    uint16_t b;
};

int main(void) {
    struct S s;
    char *base = (char*)&s;

    /* ignora o offsetof correto (=8) */
    uint16_t *p = (uint16_t*)(base + 1);

    ALIGN_ASSERT(p);
}