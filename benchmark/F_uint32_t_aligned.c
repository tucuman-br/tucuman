#include <stdint.h>
/* Grupo F — offset zero alinhado */
int main(void) {
    char buf[16];
    uint32_t *p = (uint32_t*)((char*)buf + 0);
    (void)p; return 0;
}
