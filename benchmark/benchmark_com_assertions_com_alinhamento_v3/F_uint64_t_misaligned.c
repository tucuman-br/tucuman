#include "verifier.h"
/* Grupo F — sizeof(char) desalinhado | esperado: VIOLATION */
int main(void) {
    _Alignas(uint64_t) char buf[16];
    uint64_t *p = (uint64_t*)((char*)buf + sizeof(char));
    ALIGN_ASSERT(p);
    return 0;
}
