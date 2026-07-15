#include <stdint.h>
/* Grupo D — ignorando offsetof (desalinhado) */
int main(void) {
    char buf[16];
    uint64_t *p = (uint64_t*)(buf + 1);
    uint64_t x = *p; (void)x; return 0;
}
