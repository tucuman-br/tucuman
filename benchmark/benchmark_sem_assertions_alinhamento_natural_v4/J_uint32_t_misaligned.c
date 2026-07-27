#include <stdint.h>
#include <stddef.h>

/* Grupo J — struct packed desalinhado | esperado: VIOLATION */
#pragma pack(push, 1)
struct packed_s { char a; uint32_t b; };
#pragma pack(pop)

int main(void) {
    struct packed_s obj;
    struct packed_s *ptr = &obj;
    uint32_t *q = (uint32_t *)&(ptr->b);
    uint32_t z  = *q;
    (void)z;
    return 0;
}