#include <stdint.h>
#include <stddef.h>
#include "verifier.h"

/* Grupo J — struct packed desalinhado | esperado: VIOLATION */
#pragma pack(push, 1)
struct packed_s { char a; uint64_t b; };
#pragma pack(pop)

int main(void) {
    struct packed_s obj;
    struct packed_s *ptr = &obj;
    uint64_t *q = (uint64_t *)&(ptr->b);
    uint64_t z  = *q;
    (void)z;
    ALIGN_ASSERT(q);
    return 0;
}