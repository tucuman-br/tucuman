#include <stdint.h>
/* Grupo F — sizeof(char) desalinhado */
int main(void) {
    char buf[16];
    uint16_t *p = (uint16_t*)((char*)buf + sizeof(char));
    (void)p; 
    return 0;
}
