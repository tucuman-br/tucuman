#include "verifier.h"
/* Grupo I — void* alinhado | esperado: OK */
int main(void) {
    char buf[16];
    uint32_t *p = (uint32_t*)((void*)buf + 0);
    ALIGN_ASSERT(p);
    return 0;
}
