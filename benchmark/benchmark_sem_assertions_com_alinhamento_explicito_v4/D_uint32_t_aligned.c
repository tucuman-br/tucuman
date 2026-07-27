#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo D — com offsetof (alinhado) | esperado: OK */
struct S { 
           char a; 
           uint32_t b; };
int main(void) {
    _Alignas(uint32_t) struct S s;
    char *base = (char*)&s;
    uint32_t *p = (uint32_t*)(base + offsetof(struct S, b));
    uint32_t z = *p;
    (void)z; 
    return 0;
}
