#include <stddef.h>
#include <stdint.h>
/* Grupo F — sizeof(char) desalinhado */
int main(void) {
    char buf[16];
    uint16_t *p = (uint16_t*)((char*)buf + sizeof(char));
    uint16_t z = *p;
    (void)z;  
    return 0;
}
