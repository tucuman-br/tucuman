#include <stddef.h>
#include <stdint.h>
/* Grupo F — sizeof(char) desalinhado */
int main(void) {
    char buf[16];
    uint64_t *p = (uint64_t*)((char*)buf + sizeof(char));
    uint64_t z = *p;
    (void)z; 
    return 0;
}
