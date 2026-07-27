/* Grupo D — uint32_t — ignorando offsetof (desalinhado) */
#include <stddef.h>
#include <stdint.h>

struct S { char a; uint32_t b; };

int main(void) {
    struct S s;
    char *base = (char*)&s;

    /* offset manual (=1), ignora o offsetof real da struct (respeitaria o padding) */
    uint32_t *p = (uint32_t*)(base + 1);
    uint32_t z = *p;
    (void)z;
    return 0;
}