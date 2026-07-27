#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo H — acesso packed alinhado (sp), CORRIGIDO | esperado: OK */
struct __attribute__((packed)) S {
    char a;
    char pad[sizeof(uint32_t) - 1];
    uint32_t b;
};

int main(void) {
    struct S sp;
    uint32_t *p = (uint32_t*)&sp.b;
    uint32_t z = *p;
    (void)z;
    return 0;
}