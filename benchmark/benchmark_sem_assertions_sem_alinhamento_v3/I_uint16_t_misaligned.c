#include <stdint.h>
/* Grupo I — void* desalinhado */
int main(void) {
    char buf[16];
    uint16_t *p = (uint16_t*)((void*)buf + 1);
    (void)p; 
    return 0;
}
