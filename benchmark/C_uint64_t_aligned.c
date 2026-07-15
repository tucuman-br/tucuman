#include <stdint.h>
/* Grupo C — vetor (buffer de bytes) alinhado */
int main(void) {
    char vec[32];
    uint64_t *p = (uint64_t*)&vec[8];
    uint64_t x = *p; (void)x; return 0;
}
