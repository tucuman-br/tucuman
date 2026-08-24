#include <stdint.h>
#include <stddef.h>
#include "verifier.h"/* Grupo J — struct packed | esperado: VIOLATION */
#pragma pack(push, 1)
struct packed_s { char a; uint16_t b; };
#pragma pack(pop)
int main(void) {
    struct packed_s obj;
    struct packed_s *ptr = &obj;
    uint16_t *q = (uint16_t *)&(ptr->b);  // offset = 1 → desalinhado
    uint16_t z = *q;
    (void)z;
    ALIGN_ASSERT(q);
    return 0;
}
