#include "verifier.h"
/* Grupo I — void* alinhado | esperado: OK */
int main(void) {
    _Alignas(uint32_t) char buf[16];
    uint32_t *p = (uint32_t*)((void*)buf + 0);
    return 0;
}
