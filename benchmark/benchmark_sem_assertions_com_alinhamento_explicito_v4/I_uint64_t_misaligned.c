#include <stdint.h>
#include <stddef.h>

/* Grupo I — void* desalinhado | esperado: VIOLATION */
int main(void) {
    _Alignas(uint64_t) char buf[16];
    uint64_t *p = (uint64_t*)((void*)buf + 1);
    uint64_t z = *p;
    (void)z; 
    return 0;
}
