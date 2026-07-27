#include <stdint.h>
#include <stddef.h>
/* Grupo D — com offsetof (alinhado) */
struct S { char a; uint16_t b; };
int main(void) {
    struct S s;
    char *base = (char*)&s;
    uint16_t *p = (uint16_t*)(base + offsetof(struct S, b));
    uint16_t z = *p;
    (void)z; 
    return 0;
}
