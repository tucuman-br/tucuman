#include <stddef.h>
#include <stdint.h>
/* Grupo B — padding alinhado */
int main(void) {
    uint16_t x;
    uint16_t *p = (uint16_t*)((char*)&x + 0);
    uint16_t z = *p;
    (void)z; 
    return 0;
}
