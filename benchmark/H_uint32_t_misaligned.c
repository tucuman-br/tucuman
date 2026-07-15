#include <stdint.h>
/* Grupo H — acesso a campo desalinhado (struct packed) */
struct __attribute__((packed)) S { char a; uint32_t b; };
int main(void) {
    struct S s;
    uint32_t *p = (uint32_t*)&s.b;
    (void)p; return 0;
}
