/*
 * verifier.h — Cabecalho de compatibilidade para verificadores formais
 *
 * Suporte: CBMC, ESBMC, SeaHorn, KLEE, CPAchecker, fallback nativo (GCC/Clang)
 * Padrao: SV-COMP / GNU C
 *
 * HISTORICO DE VALIDACAO EMPIRICA (sessao de revisao, ver
 * verifier_selftest_{1,2,3}_*.c para os testes usados):
 *
 *   Ferramenta       | sanity_alinhado | sanity_desalinhado | nondet_simbolico | Fix aplicado
 *   -----------------|------------------|---------------------|-------------------|----------------------------------------
 *   CBMC 6.6.0       | OK               | OK                  | OK                | nenhum (ramo original ja correto)
 *   ESBMC 8.2.0      | OK               | OK                  | OK                | __VERIFIER_assert -> assert()
 *   SeaHorn (RC0)    | OK               | OK                  | OK                | macro real e' __SEAHORN__ (nao __SEA__);
 *                    |                  |                     |                   | sassert real e' MACRO de seahorn/seahorn.h
 *                    |                  |                     |                   | (nao funcao); nondet via var. nao inicializada
 *   KLEE             | OK               | OK                  | OK                | faltava #include <assert.h>
 *                    |                  |                     |                   | (klee_assert expande p/ __assert_fail)
 *   CPAchecker 4.1   | FALHA em         | OK                  | OK                | assert() -> __VERIFIER_error() (necessario,
 *                    | TODAS as 5       |                     |                   | mas nao suficiente). LIMITACAO RESIDUAL:
 *                    | configs testadas |                     |                   | nenhuma config testada (heuristica padrao,
 *                    |                  |                     |                   | -valueAnalysis+CEX, svcomp25/BMC, kInducao,
 *                    |                  |                     |                   | valueAnalysis-NoCegar-plain) prova o caso
 *                    |                  |                     |                   | seguro (buf+0); todas acertam os casos que
 *                    |                  |                     |                   | devem violar (sem falso negativo). Tratar
 *                    |                  |                     |                   | resultados "FALSE"/violacao do CPAchecker
 *                    |                  |                     |                   | para ALIGN_ASSERT com cautela adicional.
 *
 * IMPORTANTE:
 *
 *   1) Apenas o CBMC define sua macro de identificacao (__CPROVER__)
 *      automaticamente. Para as demais ferramentas, o driver/script de
 *      build DEVE passar explicitamente a macro correspondente:
 *          esbmc      ... -D__ESBMC__
 *          sea pf     ... ja define -D__SEAHORN__ sozinho (confirmado
 *                         no log do driver; nao usar __SEA__)
 *          klee       (compilar bitcode com clang -D__KLEE__ antes de rodar klee)
 *          cpachecker ... nao define nada sozinho; -D__CPACHECKER__ e'
 *                         um nome escolhido por nos, repassado via
 *                         -setprop parser.preprocessor="cpp -D__CPACHECKER__ ..."
 *      Sem isso, a compilacao cai no fallback nativo (ou falha, se
 *      VERIFIER_ALLOW_NATIVE_FALLBACK nao estiver definido) e a
 *      verificacao NAO tera sido feita pela ferramenta pretendida.
 *
 *   2) CPAchecker: a especificacao usada precisa reconhecer
 *      __VERIFIER_error() (ex.: specification/sv-comp-reachability.spc).
 *      A config padrao/heuristica e algumas outras usam specification/
 *      default.spc, que so reconhece assert()/__assert_fail() -- nesse
 *      caso, force a spec certa via
 *      -setprop specification=<caminho>/sv-comp-reachability.spc
 *
 *   3) LIMITACAO CONHECIDA (CPAchecker 4.1): mesmo com a especificacao
 *      certa, nenhuma das 5 configuracoes de analise testadas provou
 *      corretamente o caso "ponteiro alinhado" derivado de um array de
 *      pilha com _Alignas (falso positivo sistematico). As 5 configs
 *      testadas SEMPRE acertaram os casos que devem violar (sem falso
 *      negativo). Ou seja: um "FALSE"/violacao do CPAchecker para
 *      ALIGN_ASSERT pode ser real ou pode ser esse falso positivo
 *      conhecido -- confirme manualmente antes de descartar um
 *      programa do corpus com base so' no resultado do CPAchecker.
 */
#ifndef VERIFIER_H
#define VERIFIER_H

#include <stdint.h>
#include <stddef.h>

#if defined(__CPROVER__)
    /* ── CBMC ──────────────────────────────────────────────────────── */
    #pragma message "verifier.h: branch = CBMC (__CPROVER__ detectado automaticamente)"
    #define VERIFIER_assert(cond) \
        __CPROVER_assert((cond), "alignment violation")
    static inline unsigned int VERIFIER_nondet_uint(void) {
        unsigned int x; /* variavel nao inicializada = nondet nativo do CBMC */
        return x;
    }

#elif defined(__ESBMC__)
    /* ── ESBMC ─────────────────────────────────────────────────────── */
    /* Validado empiricamente: assert() e reconhecido nativamente pelo
       ESBMC; __VERIFIER_assert NAO tem corpo e vira no-op (nao usar). */
    #pragma message "verifier.h: branch = ESBMC (__ESBMC__ passado pelo driver)"
    #include <assert.h>
    extern unsigned int __VERIFIER_nondet_uint(void); /* confirmado simbolico (k=4242 no contraexemplo) */
    #define VERIFIER_assert(cond)  assert(cond)
    #define VERIFIER_nondet_uint() __VERIFIER_nondet_uint()

#elif defined(__SEAHORN__)
    /* ── SeaHorn ───────────────────────────────────────────────────── */
    /* Validado empiricamente. Nome real da macro do driver: __SEAHORN__
       (nao __SEA__). 'sassert' e uma MACRO definida em
       seahorn/seahorn.h que chama __VERIFIER_error() -- redeclarar
       como funcao propria (erro cometido antes) faz o SeaHorn
       descartar o assert silenciosamente ("no assertion was found").
       O header nao expoe funcao de nondet dedicada; usamos a mesma
       convencao do CBMC (variavel nao inicializada), confirmada via
       selftest (resultado 'sat' no teste nondet_simbolico). */
    #pragma message "verifier.h: branch = SeaHorn (__SEAHORN__ detectado)"
    #include "seahorn/seahorn.h"
    #define VERIFIER_assert(cond)  sassert(cond)
    static inline unsigned int VERIFIER_nondet_uint(void) {
        unsigned int x;
        return x;
    }

#elif defined(__KLEE__)
    /* ── KLEE ──────────────────────────────────────────────────────── */
    /* Validado empiricamente. klee_assert() expande para
       __assert_fail(), declarado em <assert.h> (nao em klee/klee.h) --
       sem esse include o build falha com "undeclared function". */
    #pragma message "verifier.h: branch = KLEE (__KLEE__ passado pelo driver)"
    #include <assert.h>
    #include <klee/klee.h>
    #define VERIFIER_assert(cond)  klee_assert(cond)
    static inline unsigned int VERIFIER_nondet_uint(void) {
        unsigned int x;
        klee_make_symbolic(&x, sizeof(x), "nondet_uint");
        return x;
    }

#elif defined(__CPACHECKER__)
    /* ── CPAchecker ────────────────────────────────────────────────── */
    /* Necessario usar a convencao __VERIFIER_error() (nao assert()),
       e rodar com uma especificacao que a reconheca (ex.: -setprop
       specification=.../sv-comp-reachability.spc — a config padrao
       usa specification/default.spc, que ignora __VERIFIER_error()).
       ATENCAO -- LIMITACAO CONHECIDA: mesmo com a spec certa, nenhuma
       das 5 configuracoes de analise testadas (heuristica padrao,
       -valueAnalysis+CEX, svcomp25/BMC, kInducao,
       valueAnalysis-NoCegar-plain) prova corretamente o caso "ponteiro
       alinhado" (buf+0) derivado de array de pilha com _Alignas --
       falso positivo sistematico. Os casos que devem violar sao
       sempre corretamente detectados (sem falso negativo em nenhuma
       das 5 configs). Ver selftest antes de confiar em um resultado
       "TRUE" do CPAchecker para este tipo de propriedade. */
    #pragma message "verifier.h: branch = CPAchecker (__CPACHECKER__ passado pelo driver) - limitacao conhecida, ver comentario acima"
    extern void __VERIFIER_error(void);
    #define VERIFIER_assert(cond)  ((void)((cond) || (__VERIFIER_error(), 0)))
    extern unsigned int __VERIFIER_nondet_uint(void);
    #define VERIFIER_nondet_uint() __VERIFIER_nondet_uint()

#elif defined(VERIFIER_ALLOW_NATIVE_FALLBACK)
    /*
     * ── Fallback nativo (GCC/Clang, execucao local/smoke test) ──────
     * So compila se VERIFIER_ALLOW_NATIVE_FALLBACK for definido
     * explicitamente, para impedir que uma configuracao de driver
     * quebrada (macro de ferramenta ausente) caia aqui em silencio.
     * NAO fornece garantias formais: assert() e um valor
     * pseudo-aleatorio via rand(), uteis apenas para smoke test local.
     */
    #pragma message "verifier.h: branch = FALLBACK NATIVO (sem garantias formais)"
    #include <assert.h>
    #include <stdlib.h>
    #define VERIFIER_assert(cond)  assert(cond)
    static inline unsigned int VERIFIER_nondet_uint(void) {
        return (unsigned int)rand(); /* NAO simbolico: apenas smoke test */
    }

#else
    #error "verifier.h: nenhuma macro de ferramenta reconhecida " \
           "(__CPROVER__/__ESBMC__/__SEAHORN__/__KLEE__/__CPACHECKER__) e " \
           "VERIFIER_ALLOW_NATIVE_FALLBACK nao foi definido. " \
           "Verifique se o driver de build esta passando a macro " \
           "correta para a ferramenta pretendida."
#endif

/*
 * ALIGN_ASSERT(p) — verifica alinhamento natural do ponteiro p
 * Falha se: (endereco de p) % sizeof(*p) != 0
 * Validado empiricamente em CBMC, ESBMC, SeaHorn e KLEE (os 4 casos
 * de teste corretos nas 3 propriedades do selftest). Ver ressalva
 * sobre CPAchecker acima.
 */
#define ALIGN_ASSERT(p) \
    VERIFIER_assert(((uintptr_t)(p) % sizeof(*(p))) == 0)

#endif /* VERIFIER_H */
