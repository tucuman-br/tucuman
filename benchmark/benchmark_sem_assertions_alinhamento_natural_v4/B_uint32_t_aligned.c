#include <stddef.h>
#include <stdint.h>
/* Grupo B — padding alinhado */
int main(void) {
    uint32_t x;
    uint32_t *p = (uint32_t*)((char*)&x + 0);
    uint16_t z = *p;
    (void)z; 
    return 0;
}
