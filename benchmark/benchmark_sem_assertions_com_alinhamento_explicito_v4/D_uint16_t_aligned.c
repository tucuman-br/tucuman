#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo D — com offsetof (alinhado) | esperado: OK */
struct S { 
          char a; 
          uint16_t b; 
};

int main(void) {
    _Alignas(uint16_t) struct S s;
    char *base = (char*)&s;
    uint16_t *p = (uint16_t*)(base + offsetof(struct S, b));
    uint16_t z = *p;
    (void)z; 
    return 0;

}
