#include <stdint.h>
/* Grupo D — ignorando offsetof (desalinhado) */
int main(void) {
    char buf[16];
    uint32_t *p = (uint32_t*)(buf + 1);
    uint32_t x = *p; (void)x; return 0;
}
