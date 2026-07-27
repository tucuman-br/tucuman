#include <stdint.h>
#include <stddef.h>

/* Grupo I — void* alinhado | esperado: OK */
int main(void) {
    _Alignas(uint32_t) char buf[16];
    uint32_t *p = (uint32_t*)((void*)buf + 0);
    uint32_t z = *p;
    (void)z; 
    return 0;
}
