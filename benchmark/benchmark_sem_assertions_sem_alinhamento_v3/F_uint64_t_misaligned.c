#include <stdint.h>
/* Grupo F — sizeof(char) desalinhado */
int main(void) {
    char buf[16];
    uint64_t *p = (uint64_t*)((char*)buf + sizeof(char));
    (void)p; 
    return 0;
}
