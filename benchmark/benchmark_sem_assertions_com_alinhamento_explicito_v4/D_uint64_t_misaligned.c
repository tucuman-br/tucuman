#include <stdint.h>
#include <stddef.h>
/* Grupo D — ignorando offsetof (desalinhado) | esperado: VIOLATION */
struct S {
    char a;
    _Alignas(uint64_t) uint64_t b;
};

int main(void) {
    struct S s;
    char *base = (char*)&s;

    /* ignora o offsetof correto (=8) */
    uint64_t *p = (uint64_t*)(base + 1);
    uint64_t z = *p;
    (void)z; 
    return 0;
}