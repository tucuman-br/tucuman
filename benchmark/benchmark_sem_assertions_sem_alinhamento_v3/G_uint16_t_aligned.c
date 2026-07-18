#include <stdint.h>
/* Grupo G — offset multiplo alinhado */
int main(void) {
    char buf[16];
    uint16_t *p = (uint16_t*)(buf + 2);
    (void)p; 
    return 0;
}
