#include <stddef.h>
#include <stdint.h>
/* Grupo I — void* alinhado */
int main(void) {
    char buf[16];
    uint64_t *p = (uint64_t*)((void*)buf + 0);
    uint64_t z = *p;
    (void)z; 
    return 0;
}
