#include "verifier.h"
/* Grupo I — void* alinhado | esperado: OK */
int main(void) {
    char buf[16];
    uint64_t *p = (uint64_t*)((void*)buf + 0);
    ALIGN_ASSERT(p);
    return 0;
}
