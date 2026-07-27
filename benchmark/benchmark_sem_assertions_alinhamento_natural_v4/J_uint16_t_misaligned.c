#include <stdint.h>
#include <stddef.h>

/* Grupo J — struct packed desalinhado | esperado: VIOLATION */
#pragma pack(push, 1)
struct packed_s { char a; uint16_t b; };
#pragma pack(pop)

int main(void) {
    struct packed_s obj;
    struct packed_s *ptr = &obj;
    uint16_t *q = (uint16_t *)&(ptr->b);
    uint16_t z  = *q;
    (void)z;
    return 0;
}
