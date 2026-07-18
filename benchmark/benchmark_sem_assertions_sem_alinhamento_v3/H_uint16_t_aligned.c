#include <stdint.h>
/* Grupo H — acesso a campo alinhado (struct nao-packed) */
struct S { char a; uint16_t b; };
int main(void) {
    struct S sp;
    uint16_t *p = (uint16_t*)&sp.b;
    (void)p; 
    return 0;
}
