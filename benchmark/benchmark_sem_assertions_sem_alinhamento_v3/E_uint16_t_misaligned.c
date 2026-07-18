#include <stdint.h>
/* Grupo E — offset simbolico desalinhado */
unsigned nondet_uint(void);
int main(void) {
    char buf[16];
    unsigned i = nondet_uint();
    uint16_t *p = (uint16_t*)(buf + i);
    (void)p; 
    return 0;
}
