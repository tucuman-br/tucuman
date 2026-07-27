/* Grupo D — uint64_t — ignorando offsetof (desalinhado) */
#include <stddef.h>
#include <stdint.h>

struct S { char a; uint64_t b; };

int main(void) {
    struct S s;
    char *base = (char*)&s;

    /* offset manual (=1), ignora o offsetof real da struct (respeitaria o padding) */
    uint64_t *p = (uint64_t*)(base + 1);
    uint64_t z = *p;
    (void)z;
    return 0;
}