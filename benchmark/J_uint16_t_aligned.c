#include <stdint.h>
#include <stddef.h>
/* Grupo J — struct nao-packed com offsetof (alinhado) */
struct packed_s { char a; uint16_t b; };
int main(void) {
    struct packed_s obj;
    char *base = (char*)&obj;
    uint16_t *q = (uint16_t*)(base + offsetof(struct packed_s, b));
    (void)q; return 0;
}
