#include <stdint.h>
#include <stddef.h>
/* Grupo D — com offsetof (alinhado) */
struct S { char a; uint64_t b; };
int main(void) {
    struct S s;
    char *base = (char*)&s;
    uint64_t *p = (uint64_t*)(base + offsetof(struct S, b));
    (void)p; return 0;
}
