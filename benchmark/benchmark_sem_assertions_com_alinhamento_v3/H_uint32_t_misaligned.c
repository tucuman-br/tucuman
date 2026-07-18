#include "verifier.h"
/* Grupo H — acesso bruto desalinhado (s) | esperado: VIOLATION */
struct __attribute__((packed)) S {
    char a;
    uint32_t b;
};
int main(void) {
    struct S s;
    uint32_t *p = (uint32_t*)&s.b;
    return 0;
}
