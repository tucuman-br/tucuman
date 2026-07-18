#include <stdint.h>
/* Grupo C — vetor (buffer de bytes) alinhado */
int main(void) {
    char vec[32];
    uint16_t *p = (uint16_t*)&vec[2];
    uint16_t x = *p; 
    (void)x; 
    return 0;
}

