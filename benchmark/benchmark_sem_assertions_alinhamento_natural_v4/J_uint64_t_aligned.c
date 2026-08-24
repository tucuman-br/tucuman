#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo J — struct nao-packed | esperado: OK */
struct packed_s { char a; uint64_t b; };
int main(void) {
    struct packed_s obj;
    struct packed_s *ptr = &obj;
    uint64_t *q = (uint64_t *)&(ptr->b);  // offset = 2 → alinhado
    uint64_t z = *q;
    (void)z;
    return 0;
}