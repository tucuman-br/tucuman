#include <stddef.h>
#include <stdint.h>
/* Grupo B — padding desalinhado */
int main(void) {
    uint64_t x;
    uint64_t *p = (uint64_t*)((char*)&x + 1);
    uint16_t z = *p;
    (void)z; 
    return 0;
}
