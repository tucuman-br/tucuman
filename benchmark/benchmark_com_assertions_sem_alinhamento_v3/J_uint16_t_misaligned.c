#include "verifier.h"
/* Grupo J — struct packed desalinhado | esperado: VIOLATION */
struct __attribute__((packed)) packed_s { char a; uint16_t b; };
int main(void) {
    struct packed_s obj;
    struct packed_s *ptr = &obj;
    uint16_t *q = (uint16_t*)&((struct packed_s*)ptr)->b;
    ALIGN_ASSERT(q);
    return 0;
}
