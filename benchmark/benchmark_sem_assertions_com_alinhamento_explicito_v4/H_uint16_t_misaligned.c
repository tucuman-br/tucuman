#include <stdint.h>
#include <stddef.h>

/* Grupo H — acesso bruto desalinhado (s) | esperado: VIOLATION */
struct __attribute__((packed)) S {
    char a;
    uint16_t b;
};

int main(void) {
    struct S s;
    uint16_t *p = (uint16_t*)&s.b;
    uint16_t z = *p;
    (void)z; 
    return 0;
}
