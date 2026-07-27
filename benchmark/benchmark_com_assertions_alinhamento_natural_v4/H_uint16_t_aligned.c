#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo H — acesso packed alinhado (sp), CORRIGIDO | esperado: OK */
struct __attribute__((packed)) S {
    char a;
    char pad[sizeof(uint16_t) - 1];
    uint16_t b;
};

int main(void) {
    struct S sp;
    uint16_t *p = (uint16_t*)&sp.b;
    uint16_t z = *p;
    (void)z;
    ALIGN_ASSERT(p);
    return 0;
}
