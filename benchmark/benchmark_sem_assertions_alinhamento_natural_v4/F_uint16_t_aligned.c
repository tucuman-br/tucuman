#include <stddef.h>
#include <stdint.h>
/* Grupo F — offset zero alinhado */
int main(void) {
    char buf[16];
    uint16_t *p = (uint16_t*)((char*)buf + 0);
    uint16_t z = *p;
    (void)z;  
    return 0;
}
