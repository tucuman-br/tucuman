#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo J — struct nao-packed | esperado: OK */
struct packed_s { char a; uint32_t b; };
int main(void) {
    _Alignas(uint32_t) struct packed_s obj;
    struct packed_s *ptr = &obj;
    uint32_t *q = (uint32_t *)&(ptr->b);  // offset = 2 → alinhado
    uint32_t z = *q;
    (void)z;
    ALIGN_ASSERT(q);
    return 0;
}
