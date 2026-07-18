#include <stdint.h>
/* Grupo B — padding alinhado */
int main(void) {
    uint64_t x;
    uint64_t *p = (uint64_t*)((char*)&x + 0);
    (void)p; 
    return 0;
}
