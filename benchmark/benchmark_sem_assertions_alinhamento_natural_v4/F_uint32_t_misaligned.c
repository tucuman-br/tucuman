#include <stddef.h>
#include <stdint.h>
/* Grupo F — sizeof(char) desalinhado */
int main(void) {
    char buf[16];
    uint32_t *p = (uint32_t*)((char*)buf + sizeof(char));
    uint32_t z = *p;
    (void)z; 
    return 0;
}
