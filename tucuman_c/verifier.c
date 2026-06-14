// verifier.c
#include "verifier.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

static const char *group_label[] = {
    "A - Offset Constante",
    "B - Padding",
    "C - Vetor",
    "D - offsetof",
    "E - Simbolico",
    "F - sizeof(char)",
    "G - Offset Impar",
    "H - Campo Struct",
    "I - void*",
    "J - Struct Packed"
};

static const char *result_label(SmtResult r) {
    switch (r) {
        case SMT_VIOLATION:          return "VIOLACAO";
        case SMT_OK:                 return "OK";
        case SMT_POSSIBLE_VIOLATION: return "POSSIVEL VIOLACAO";
        case SMT_UNKNOWN:            return "UNKNOWN";
        default:                     return "UNKNOWN";
    }
}

/* ─────────────────────────────────────────
   Processa um caso
───────────────────────────────────────── */
VerifierEntry verifier_check(const ParsedCase *c) {
    VerifierEntry entry = {0};

    // chama o modelo SMT
    SmtOutput smt = smt_check(c);

    // preenche a entrada
    strncpy(entry.id,       c->id,                    sizeof(entry.id) - 1);
    strncpy(entry.group,    group_label[c->group],    sizeof(entry.group) - 1);
    strncpy(entry.ptr_type, c->ptr_type,              sizeof(entry.ptr_type) - 1);
    strncpy(entry.result,   result_label(smt.result), sizeof(entry.result) - 1);
    strncpy(entry.message,  smt.message,              sizeof(entry.message) - 1);

    entry.alignment   = c->alignment;
    entry.line_number = c->line_number;

    // contra-exemplo
    if (smt.has_counterexample)
        snprintf(entry.counterexample, sizeof(entry.counterexample),
                 "%llu", (unsigned long long)smt.counterexample);
    else
        strncpy(entry.counterexample, "-", sizeof(entry.counterexample) - 1);

    return entry;
}

/* ─────────────────────────────────────────
   Gera CSV
───────────────────────────────────────── */
int verifier_write_csv(const VerifierEntry *entries,
                       int count,
                       const char *filepath,
                       const char *src_file) {
    FILE *fp = fopen(filepath, "w");
    if (!fp) {
        fprintf(stderr, "verifier: nao foi possivel criar '%s'\n", filepath);
        return 0;
    }

    // cabeçalho do relatório
    time_t now = time(NULL);
    char timebuf[64];
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", localtime(&now));

    fprintf(fp, "# Tucuma — Relatorio de Verificacao de Alinhamento\n");
    fprintf(fp, "# Arquivo analisado : %s\n", src_file);
    fprintf(fp, "# Data              : %s\n", timebuf);
    fprintf(fp, "# Total de casos    : %d\n", count);

    // contagem por resultado
    int n_vio = 0, n_ok = 0, n_poss = 0, n_unk = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(entries[i].result, "VIOLACAO")          == 0) n_vio++;
        else if (strcmp(entries[i].result, "OK")           == 0) n_ok++;
        else if (strcmp(entries[i].result, "POSSIVEL VIOLACAO") == 0) n_poss++;
        else n_unk++;
    }

    fprintf(fp, "# Violacoes         : %d\n", n_vio);
    fprintf(fp, "# OK                : %d\n", n_ok);
    fprintf(fp, "# Possivel Violacao : %d\n", n_poss);
    fprintf(fp, "# Unknown           : %d\n", n_unk);
    fprintf(fp, "#\n");

    // cabeçalho CSV
    fprintf(fp, "ID,Grupo,Tipo,Alinhamento,Resultado,Mensagem,Contra-exemplo,Linha\n");

    // linhas
    for (int i = 0; i < count; i++) {
        const VerifierEntry *e = &entries[i];
        fprintf(fp, "%s,\"%s\",%s,%llu,%s,\"%s\",%s,%d\n",
                e->id,
                e->group,
                e->ptr_type,
                (unsigned long long)e->alignment,
                e->result,
                e->message,
                e->counterexample,
                e->line_number);
    }

    fclose(fp);
    return 1;
}