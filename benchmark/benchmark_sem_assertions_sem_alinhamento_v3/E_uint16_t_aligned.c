#include <stdint.h>
/* Grupo E — offset constante alinhado */
int main(void) {
    char buf[16];
    uint16_t *p = (uint16_t*)(buf + 2);
    (void)p;
    return 0;
}
