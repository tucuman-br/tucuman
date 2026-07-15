#include <stdint.h>
/* Grupo F — offset zero alinhado */
int main(void) {
    char buf[16];
    uint64_t *p = (uint64_t*)((char*)buf + 0);
    (void)p; return 0;
}
