#include <stdint.h>
#include <stddef.h>

/* Grupo I — void* desalinhado | esperado: VIOLATION */
int main(void) {
    _Alignas(uint32_t) char buf[16];
    uint32_t *p = (uint32_t*)((void*)buf + 1);
    uint32_t z = *p;
    (void)z; 
    return 0;
}
