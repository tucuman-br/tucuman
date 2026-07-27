#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo H — acesso packed alinhado (sp), CORRIGIDO | esperado: OK */
struct __attribute__((packed)) S {
    char a;
    char pad[sizeof(uint64_t) - 1];
    uint64_t b;
};

int main(void) {
    struct S sp;
    uint64_t *p = (uint64_t*)&sp.b;
    uint64_t z = *p;
    (void)z;
    return 0;
}