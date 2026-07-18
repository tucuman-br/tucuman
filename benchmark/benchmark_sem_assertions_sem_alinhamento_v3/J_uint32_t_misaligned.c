#include <stdint.h>
/* Grupo J — struct packed desalinhado */
struct __attribute__((packed)) packed_s { char a; uint32_t b; };
int main(void) {
    struct packed_s obj;
    struct packed_s *ptr = &obj;
    uint32_t *q = (uint32_t*)&((struct packed_s*)ptr)->b;
    (void)q; 
    return 0;
}
