#include "verifier.h"
/* Grupo H — acesso bruto desalinhado (s) | esperado: VIOLATION */
/* Grupo H — acesso a campo desalinhado (struct packed) */
struct __attribute__((packed)) S { char a; uint64_t b; };
int main(void) {
    struct S s;
    uint64_t *p = (uint64_t*)&s.b;
    (void)p; 
    ALIGN_ASSERT(p);
    return 0;
}
