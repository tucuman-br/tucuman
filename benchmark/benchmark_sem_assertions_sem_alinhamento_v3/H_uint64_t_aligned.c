#include <stdint.h>
/* Grupo H — acesso a campo alinhado (struct nao-packed) */
struct S { char a; uint64_t b; };
int main(void) {
    struct S sp;
    uint64_t *p = (uint64_t*)&sp.b;
    (void)p; 
    return 0;
}
