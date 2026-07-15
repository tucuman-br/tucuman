#include <stdint.h>
/* Grupo I — void* desalinhado */
int main(void) {
    char buf[16];
    uint32_t *p = (uint32_t*)((void*)buf + 1);
    (void)p; return 0;
}
