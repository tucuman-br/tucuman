#include "verifier.h"
struct S {
    char a;
    uint64_t b;
};

int main(void) {
    struct S s;
    char *base = (char*)&s;

    /* ignora o offsetof correto (=8) */
    uint64_t *p = (uint64_t*)(base + 1);
    return 0;
}