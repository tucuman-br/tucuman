#include <stddef.h>
#include <stdint.h>
/* Grupo I — void* alinhado */
int main(void) {
    char buf[16];
    uint16_t *p = (uint16_t*)((void*)buf + 0);
    uint16_t z = *p;
    (void)z; 
    return 0;
}
