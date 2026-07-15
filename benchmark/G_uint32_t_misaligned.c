#include <stdint.h>
/* Grupo G — offset impar desalinhado */
int main(void) {
    char buf[16];
    uint32_t *p = (uint32_t*)(buf + 5);
    (void)p; return 0;
}
