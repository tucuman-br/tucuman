#include "verifier.h"
/* Grupo I — void* alinhado | esperado: OK */
int main(void) {
     _Alignas(uint64_t)char buf[16];
    uint64_t *p = (uint64_t*)((void*)buf + 0);
    return 0;
}
