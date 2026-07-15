#include <stdint.h>
/* Grupo A — offset constante desalinhado */
int main(void) {
    char buf[16];
    uint64_t *p = (uint64_t*)(buf + 1);
    uint64_t x = *p; (void)x;
    return 0;
}
