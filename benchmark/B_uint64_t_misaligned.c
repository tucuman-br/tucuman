#include <stdint.h>
/* Grupo B — padding desalinhado */
int main(void) {
    uint64_t x;
    uint64_t *p = (uint64_t*)((char*)&x + 1);
    (void)p; return 0;
}
