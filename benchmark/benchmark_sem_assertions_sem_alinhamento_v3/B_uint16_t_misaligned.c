#include <stdint.h>
/* Grupo B — padding desalinhado */
int main(void) {
    uint16_t x;
    uint16_t *p = (uint16_t*)((char*)&x + 1);
    (void)p; 
    return 0;
}
