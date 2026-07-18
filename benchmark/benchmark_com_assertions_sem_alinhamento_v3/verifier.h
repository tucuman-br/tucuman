/*
 * verifier.h — Cabecalho de compatibilidade para verificadores formais
 *
 * Suporte: CBMC, ESBMC, CPAchecker, KLEE, SeaHorn, Tucuma
 * Padrao: SV-COMP / GNU C
 */
#ifndef VERIFIER_H
#define VERIFIER_H


/* Inteiros */

typedef signed char         int8_t;
typedef unsigned char       uint8_t;

typedef short               int16_t;
typedef unsigned short      uint16_t;

typedef int                 int32_t;
typedef unsigned int        uint32_t;

typedef long long           int64_t;
typedef unsigned long long  uint64_t;

/* Tipos auxiliares */

//typedef unsigned long       uintptr_t;
//typedef unsigned long       size_t;

//#include <stdint.h>
//#include <stddef.h>

#if defined(__CPROVER__)
    /* ── CBMC ──────────────────────────────────────────────────────── */
    #define VERIFIER_assert(cond) \
        __CPROVER_assert((cond), "alignment violation")
    static inline unsigned int VERIFIER_nondet_uint(void) {
        unsigned int x;
        return x;
    }

#elif defined(__ESBMC__)
    /* ── ESBMC ─────────────────────────────────────────────────────── */
    extern void         __VERIFIER_assert(int cond);
    extern unsigned int __VERIFIER_nondet_uint(void);
    #define VERIFIER_assert(cond)  __VERIFIER_assert(cond)
    #define VERIFIER_nondet_uint() __VERIFIER_nondet_uint()

#elif defined(__SEA__)
    /* ── SeaHorn ───────────────────────────────────────────────────── */
    extern void         sassert(int cond);
    extern unsigned int nd_uint(void);
    #define VERIFIER_assert(cond)  sassert(cond)
    #define VERIFIER_nondet_uint() nd_uint()

#elif defined(__KLEE__)
    /* ── KLEE ──────────────────────────────────────────────────────── */
    #include <klee/klee.h>
    #define VERIFIER_assert(cond)  klee_assert(cond)
    static inline unsigned int VERIFIER_nondet_uint(void) {
        unsigned int x;
        klee_make_symbolic(&x, sizeof(x), "nondet_uint");
        return x;
    }

#else
    /* ── Fallback: assert.h padrao (GCC, Clang, Tucuma) ───────────── */
    #include <assert.h>
    #define VERIFIER_assert(cond)  assert(cond)
    static inline unsigned int VERIFIER_nondet_uint(void) {
        return 0u; /* Tucuma modela como variavel livre Z3 */
    }
#endif

/*
 * ALIGN_ASSERT(p) — verifica alinhamento natural do ponteiro p
 * Falha se: (endereco de p) % sizeof(*p) != 0
 */
#define ALIGN_ASSERT(p) \
    VERIFIER_assert(((uintptr_t)(p) % sizeof(*(p))) == 0)

#endif /* VERIFIER_H */
