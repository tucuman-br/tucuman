#include "verifier.h"
/* Grupo D — ignorando offsetof (desalinhado) | esperado: VIOLATION */
struct S {
    char a;
    uint32_t b;
};

int main(void) {
    struct S s;
    char *base = (char*)&s;

    /* ignora o offsetof correto (=8) */
    uint32_t *p = (uint32_t*)(base + 1);
   return 0;
}