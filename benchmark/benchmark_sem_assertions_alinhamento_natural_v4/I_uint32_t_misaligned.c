#include <stddef.h>
#include <stdint.h>
/* Grupo I — void* desalinhado */
int main(void) {
    char buf[16];
    uint32_t *p = (uint32_t*)((void*)buf + 1);
    uint32_t z = *p;
    (void)z;  
    return 0;
}
