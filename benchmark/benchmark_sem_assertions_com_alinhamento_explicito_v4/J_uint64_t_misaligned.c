#include <stdint.h>
#include <stddef.h>
#include "verifier.h"
/* Grupo J — struct packed | esperado: VIOLATION */
#pragma pack(push, 1)
struct packed_s { char a; uint64_t b; };
#pragma pack(pop)
int main(void) {
    _Alignas(uint64_t) struct packed_s obj;
    struct packed_s *ptr = &obj;
    uint64_t *q = (uint64_t *)&(ptr->b);  // offset = 1 → desalinhado
    uint64_t z = *q;
    (void)z;
    return 0;
}
