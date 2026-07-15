#include <stdint.h>
/* Grupo G — offset multiplo alinhado */
int main(void) {
    char buf[16];
    uint32_t *p = (uint32_t*)(buf + 4);
    (void)p; return 0;
}
