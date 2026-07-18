#include "verifier.h"
/* Grupo H — acesso bruto desalinhado (s) | esperado: VIOLATION */
struct __attribute__((packed)) S {
    char a;
    uint16_t b;
};

int main(void) {
    struct S s;
    uint16_t *p = (uint16_t*)&s.b;
    return 0;
}