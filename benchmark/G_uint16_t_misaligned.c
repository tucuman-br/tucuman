#include <stdint.h>
/* Grupo G — offset impar desalinhado */
int main(void) {
    char buf[16];
    uint16_t *p = (uint16_t*)(buf + 3);
    (void)p; return 0;
}
