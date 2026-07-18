#include <stdint.h>
/* Grupo F — sizeof(char) desalinhado */
int main(void) {
    char buf[16];
    uint32_t *p = (uint32_t*)((char*)buf + sizeof(char));
    (void)p; 
    return 0;
}
