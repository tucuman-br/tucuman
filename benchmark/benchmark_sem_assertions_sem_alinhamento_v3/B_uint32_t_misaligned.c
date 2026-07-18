#include <stdint.h>
/* Grupo B — padding desalinhado */
int main(void) {
    uint32_t x;
    uint32_t *p = (uint32_t*)((char*)&x + 1);
    (void)p; 
    return 0;
}
