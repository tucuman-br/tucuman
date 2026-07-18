#include <stdint.h>
/* Grupo I — void* alinhado */
int main(void) {
    char buf[16];
    uint64_t *p = (uint64_t*)((void*)buf + 0);
    (void)p;
    return 0;
}
