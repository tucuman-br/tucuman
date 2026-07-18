#include <stdint.h>
/* Grupo D — ignorando offsetof (desalinhado) */
int main(void) {
    char buf[16];
    uint16_t *p = (uint16_t*)(buf + 1);
    uint16_t x = *p; 
    (void)x; 
    return 0;
}
