#include <stdint.h>
/* Grupo A — offset constante alinhado */
int main(void) {
    char buf[16];
    uint64_t *p = (uint64_t*)(buf + 0);
    uint64_t x = *p; (void)x;
    return 0;
}
