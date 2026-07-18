#include "verifier.h"
/* Grupo I — void* alinhado | esperado: OK */
int main(void) {
    _Alignas(uint16_t) char buf[16];
    uint16_t *p = (uint16_t*)((void*)buf + 0);
    ALIGN_ASSERT(p);
    return 0;
}
