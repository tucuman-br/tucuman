// test_z3.c — teste de linkagem com Z3
#include <stdio.h>
#include <z3.h>

int main(void) {
    Z3_config  cfg = Z3_mk_config();
    Z3_context ctx = Z3_mk_context(cfg);
    Z3_del_config(cfg);

    printf("Z3 versao: %s\n", Z3_get_full_version());

    Z3_del_context(ctx);
    return 0;
}