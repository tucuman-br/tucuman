#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo J — struct nao-packed com offsetof (alinhado) | esperado: OK */
struct packed_s { 
                  char a; 
                  uint64_t b; 
};

int main(void) {
    _Alignas(uint64_t) struct packed_s obj;
    char *base = (char*)&obj;
    uint64_t *q = (uint64_t*)(base + offsetof(struct packed_s, b));
    uint64_t z = *q;
    (void)z; 
    return 0;
}
