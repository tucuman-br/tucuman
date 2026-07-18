#include <stdint.h>
/* Grupo C — vetor (buffer de bytes) desalinhado */
int main(void) {
    char vec[32];
    uint16_t *p = (uint16_t*)&vec[3];
    uint16_t x = *p; 
    (void)x; 
    return 0;
}
