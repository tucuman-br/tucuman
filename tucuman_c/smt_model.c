// smt_model.c
#include "smt_model.h"
#include <stdio.h>
#include <string.h>

/* ─────────────────────────────────────────
   Auxiliares Z3
───────────────────────────────────────── */

// cria bitvector de 64 bits com valor constante
static Z3_ast bv64(Z3_context ctx, uint64_t val) {
    return Z3_mk_unsigned_int64(ctx, val, Z3_mk_bv_sort(ctx, 64));
}

// cria variável bitvector de 64 bits
static Z3_ast bv64_var(Z3_context ctx, const char *name) {
    return Z3_mk_const(ctx,
               Z3_mk_string_symbol(ctx, name),
               Z3_mk_bv_sort(ctx, 64));
}

// restrição de alinhamento: URem(addr, align) == 0
static Z3_ast aligned_constraint(Z3_context ctx,
                                  Z3_ast addr,
                                  uint64_t alignment) {
    Z3_ast align = bv64(ctx, alignment);
    Z3_ast zero  = bv64(ctx, 0);
    Z3_ast rem   = Z3_mk_bvurem(ctx, addr, align);
    return Z3_mk_eq(ctx, rem, zero);
}

// restrição de desalinhamento: URem(addr, align) != 0
static Z3_ast misaligned_constraint(Z3_context ctx,
                                     Z3_ast addr,
                                     uint64_t alignment) {
    Z3_ast align = bv64(ctx, alignment);
    Z3_ast zero  = bv64(ctx, 0);
    Z3_ast rem   = Z3_mk_bvurem(ctx, addr, align);
    return Z3_mk_not(ctx, Z3_mk_eq(ctx, rem, zero));
}

/* ─────────────────────────────────────────
   Verificação para offset constante
   Grupos A, B, C, F, G, H, I
───────────────────────────────────────── */
static SmtOutput check_constant_offset(Z3_context ctx,
                                        Z3_solver sol,
                                        const ParsedCase *c,
                                        uint64_t offset) {
    SmtOutput out = {0};

    // base_addr — variável livre, mas múltiplo do alinhamento natural
    Z3_ast base   = bv64_var(ctx, "base");
    Z3_ast align  = bv64(ctx, c->alignment);
    Z3_ast zero   = bv64(ctx, 0);

    // base é naturalmente alinhado: URem(base, align) == 0
    Z3_ast base_aligned = Z3_mk_eq(ctx,
                              Z3_mk_bvurem(ctx, base, align),
                              zero);
    Z3_solver_assert(ctx, sol, base_aligned);

    // addr = base + offset
    Z3_ast off  = bv64(ctx, offset);
    Z3_ast addr = Z3_mk_bvadd(ctx, base, off);

    // pergunta: addr satisfaz o alinhamento?
    Z3_ast constraint = aligned_constraint(ctx, addr, c->alignment);
    Z3_solver_assert(ctx, sol, constraint);

    Z3_lbool result = Z3_solver_check(ctx, sol);

    if (result == Z3_L_FALSE) {
        // UNSAT — nenhum base satisfaz o alinhamento → violação
        out.result = SMT_VIOLATION;
        snprintf(out.message, sizeof(out.message),
                 "VIOLACAO: offset %llu nao satisfaz alinhamento de %llu bytes",
                 (unsigned long long)offset,
                 (unsigned long long)c->alignment);
    } else if (result == Z3_L_TRUE) {
        // SAT — existe base que alinha → OK
        out.result = SMT_OK;
        snprintf(out.message, sizeof(out.message),
                 "OK: offset %llu satisfaz alinhamento de %llu bytes",
                 (unsigned long long)offset,
                 (unsigned long long)c->alignment);
    } else {
        out.result = SMT_UNKNOWN;
        snprintf(out.message, sizeof(out.message), "UNKNOWN");
    }

    return out;
}

/* ─────────────────────────────────────────
   Verificação para offset simbólico
   Grupo E
───────────────────────────────────────── */
static SmtOutput check_symbolic_offset(Z3_context ctx,
                                        Z3_solver sol,
                                        const ParsedCase *c) {
    SmtOutput out = {0};

    // base_addr — naturalmente alinhado
    Z3_ast base  = bv64_var(ctx, "base");
    Z3_ast align = bv64(ctx, c->alignment);
    Z3_ast zero  = bv64(ctx, 0);

    Z3_ast base_aligned = Z3_mk_eq(ctx,
                              Z3_mk_bvurem(ctx, base, align),
                              zero);
    Z3_solver_assert(ctx, sol, base_aligned);

    // i — offset simbólico com restrição 0 <= i < sym_upper_bound
    Z3_ast i     = bv64_var(ctx, "i");
    Z3_ast bound = bv64(ctx, c->sym_upper_bound);

    // 0 <= i (sem sinal — sempre verdade para bvugt com zero)
    Z3_ast i_ge_zero = Z3_mk_bvuge(ctx, i, zero);
    // i < bound
    Z3_ast i_lt_bound = Z3_mk_bvult(ctx, i, bound);

    Z3_solver_assert(ctx, sol, i_ge_zero);
    Z3_solver_assert(ctx, sol, i_lt_bound);

    // addr = base + i
    Z3_ast addr = Z3_mk_bvadd(ctx, base, i);

    // pergunta: existe i que viola o alinhamento?
    Z3_ast misaligned = misaligned_constraint(ctx, addr, c->alignment);
    Z3_solver_assert(ctx, sol, misaligned);

    Z3_lbool result = Z3_solver_check(ctx, sol);

    if (result == Z3_L_TRUE) {
        // SAT — encontrou i que viola → possível violação
        out.result = SMT_POSSIBLE_VIOLATION;
        out.has_counterexample = 1;

        // extrai contra-exemplo
        Z3_model model = Z3_solver_get_model(ctx, sol);
        Z3_ast   val   = NULL;
        if (Z3_model_eval(ctx, model, i, 1, &val)) {
            uint64_t ce = 0;
            Z3_get_numeral_uint64(ctx, val, &ce);
            out.counterexample = ce;
            snprintf(out.message, sizeof(out.message),
                     "POSSIVEL VIOLACAO: i=%llu viola alinhamento de %llu bytes",
                     (unsigned long long)ce,
                     (unsigned long long)c->alignment);
        }
    } else if (result == Z3_L_FALSE) {
        // UNSAT — todo i dentro do bound alinha → OK
        out.result = SMT_OK;
        snprintf(out.message, sizeof(out.message),
                 "OK: todo i em [0,%llu) satisfaz alinhamento de %llu bytes",
                 (unsigned long long)c->sym_upper_bound,
                 (unsigned long long)c->alignment);
    } else {
        out.result = SMT_UNKNOWN;
        snprintf(out.message, sizeof(out.message), "UNKNOWN");
    }

    return out;
}

/* ─────────────────────────────────────────
   Offset real para Grupo J (packed)
   layout: sem padding entre campos
───────────────────────────────────────── */
static uint64_t packed_offset_of_b(const char *ptr_type) {
    // struct packed_s { char a; uintX_t b; }
    // sem padding: b fica sempre em offset 1
    (void)ptr_type;
    return 1;
}

/* ─────────────────────────────────────────
   Dispatcher principal
───────────────────────────────────────── */
SmtOutput smt_check(const ParsedCase *c) {
    Z3_config  cfg = Z3_mk_config();
    Z3_context ctx = Z3_mk_context(cfg);
    Z3_del_config(cfg);
    Z3_solver  sol = Z3_mk_solver(ctx);
    Z3_solver_inc_ref(ctx, sol);

    SmtOutput out = {0};

    switch (c->group) {
        // offset constante — verifica diretamente
        case GROUP_A:
        case GROUP_B:
        case GROUP_C:
        case GROUP_F:
        case GROUP_I:
            out = check_constant_offset(ctx, sol, c, c->offset);
            break;

        // offset impar arbitrario
        case GROUP_G:
            out = check_constant_offset(ctx, sol, c, c->offset);
            break;

        // offsetof — offset 0 significa alinhado por construção
        case GROUP_D:
            out = check_constant_offset(ctx, sol, c, 0);
            break;

        // offset simbólico
        case GROUP_E:
            out = check_symbolic_offset(ctx, sol, c);
            break;

        // acesso bruto ignorando padding — offset = 1
        case GROUP_H:
            out = check_constant_offset(ctx, sol, c, 1);
            break;

        // struct packed — offset real = 1 (char a antes de b)
        case GROUP_J:
            out = check_constant_offset(ctx, sol, c,
                      packed_offset_of_b(c->ptr_type));
            break;

        default:
            out.result = SMT_UNKNOWN;
            snprintf(out.message, sizeof(out.message),
                     "grupo nao suportado");
            break;
    }

    Z3_solver_dec_ref(ctx, sol);
    Z3_del_context(ctx);
    return out;
}