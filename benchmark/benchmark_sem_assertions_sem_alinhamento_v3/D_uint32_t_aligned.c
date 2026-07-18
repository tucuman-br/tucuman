#include <stdint.h>
#include <stddef.h>
/* Grupo D — com offsetof (alinhado) */
struct S { char a; uint32_t b; };
int main(void) {
    struct S s;
    char *base = (char*)&s;
    uint32_t *p = (uint32_t*)(base + offsetof(struct S, b));
    (void)p; 
    return 0;
}
