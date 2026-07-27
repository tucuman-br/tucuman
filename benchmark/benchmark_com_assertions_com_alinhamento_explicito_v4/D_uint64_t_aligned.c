#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo D — com offsetof (alinhado) | esperado: OK */
struct S { 
          char a; 
          uint64_t b; 
};

int main(void) {
    _Alignas(uint64_t) struct S s;
    char *base = (char*)&s;
    uint64_t *p = (uint64_t*)(base + offsetof(struct S, b));
    uint64_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}
