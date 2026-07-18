#include "verifier.h"
/* Grupo I — void* desalinhado | esperado: VIOLATION */
int main(void) {
    char buf[16];
    uint64_t *p = (uint64_t*)((void*)buf + 1);
    ALIGN_ASSERT(p);
    return 0;
}
