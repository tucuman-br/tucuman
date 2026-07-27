#include <stdint.h>
#include <stddef.h>

/* Grupo H — acesso bruto desalinhado (s) | esperado: VIOLATION */
struct __attribute__((packed)) S {
    char a;
    uint64_t b;
};

int main(void) {
    struct S s;
    uint64_t *p = (uint64_t*)&s.b;
    uint64_t z = *p;
    (void)z; 
    return 0;
}
