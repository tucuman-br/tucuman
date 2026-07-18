#include "verifier.h"
/* Grupo F — offset zero alinhado | esperado: OK */
int main(void) {
    char buf[16];
    uint32_t *p = (uint32_t*)((char*)buf + 0);
    ALIGN_ASSERT(p);
    return 0;
}
