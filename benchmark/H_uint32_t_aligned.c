#include <stdint.h>
/* Grupo H — acesso a campo alinhado (struct nao-packed) */
struct S { char a; uint32_t b; };
int main(void) {
    struct S sp;
    uint32_t *p = (uint32_t*)&sp.b;
    (void)p; return 0;
}
