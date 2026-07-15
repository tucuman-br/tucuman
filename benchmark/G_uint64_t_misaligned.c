#include <stdint.h>
/* Grupo G — offset impar desalinhado */
int main(void) {
    char buf[16];
    uint64_t *p = (uint64_t*)(buf + 7);
    (void)p; return 0;
}
