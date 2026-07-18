#include <stdint.h>
/* Grupo G — offset multiplo alinhado */
int main(void) {
    char buf[16];
    uint64_t *p = (uint64_t*)(buf + 8);
    (void)p; 
    return 0;
}
