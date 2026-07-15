#include <stdint.h>
/* Grupo I — void* alinhado */
int main(void) {
    char buf[16];
    uint32_t *p = (uint32_t*)((void*)buf + 0);
    (void)p; return 0;
}
