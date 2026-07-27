/* Grupo D — uint16_t — ignorando offsetof (desalinhado) */
#include <stddef.h>
#include <stdint.h>

struct S { char a; uint16_t b; };

int main(void) {
    struct S s;
    char *base = (char*)&s;

    /* offset manual (=1), ignora o offsetof real da struct (respeitaria o padding) */
    uint16_t *p = (uint16_t*)(base + 1);
    uint16_t z = *p;
    (void)z;
    return 0;
}