#include <stdint.h>
/* Grupo C — vetor (buffer de bytes) alinhado */
int main(void) {
    char vec[32];
    uint32_t *p = (uint32_t*)&vec[4];
    uint32_t x = *p; 
    (void)x; 
    return 0;
}
