// benchmark_runner.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "parser.h"
#include "smt_model.h"
#include "verifier.h"

#define MAX_FILES   64
#define MAX_ENTRIES 512

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo1.c> [arquivo2.c ...]\n", argv[0]);
        fprintf(stderr, "  ou: %s *.c\n", argv[0]);
        return 1;
    }

    // array consolidado de todas as entradas
    VerifierEntry *all_entries = calloc(MAX_ENTRIES, sizeof(VerifierEntry));
    char          *all_files   = calloc(MAX_ENTRIES, 256);
    int            total       = 0;

    if (!all_entries || !all_files) {
        fprintf(stderr, "erro: sem memoria\n");
        return 1;
    }

    printf("=== Tucuman Benchmark Runner ===\n");
    printf("Arquivos: %d\n\n", argc - 1);

    // estatísticas por arquivo
    printf("%-35s  %6s  %8s  %5s  %10s  %10s\n",
           "Arquivo", "Casos", "Violacao", "OK", "Poss.Vio.", "Unknown");
    printf("%-35s  %6s  %8s  %5s  %10s  %10s\n",
           "-----------------------------------",
           "------", "--------", "-----",
           "----------", "----------");

    for (int f = 1; f < argc; f++) {
        const char *filepath = argv[f];

        // extrai nome do arquivo sem path
        const char *fname = filepath;
        const char *p = filepath;
        while (*p) {
            if (*p == '/' || *p == '\\') fname = p + 1;
            p++;
        }

        // parser
        int count = 0;
        ParsedCase *cases = parser_parse_file(filepath, &count);

        if (!cases || count == 0) {
            printf("%-35s  %6d  (nenhum padrao reconhecido)\n", fname, 0);
            if (cases) parser_free(cases);
            continue;
        }

        int n_vio = 0, n_ok = 0, n_poss = 0, n_unk = 0;

        for (int i = 0; i < count && total < MAX_ENTRIES; i++) {
            VerifierEntry entry = verifier_check(&cases[i]);

            // guarda nome do arquivo junto com a entrada
            strncpy(all_files + total * 256, fname, 255);
            all_entries[total++] = entry;

            if      (strcmp(entry.result, "VIOLACAO")          == 0) n_vio++;
            else if (strcmp(entry.result, "OK")                == 0) n_ok++;
            else if (strcmp(entry.result, "POSSIVEL VIOLACAO") == 0) n_poss++;
            else n_unk++;
        }

        printf("%-35s  %6d  %8d  %5d  %10d  %10d\n",
               fname, count, n_vio, n_ok, n_poss, n_unk);

        parser_free(cases);
    }

    // totais
    int t_vio = 0, t_ok = 0, t_poss = 0, t_unk = 0;
    for (int i = 0; i < total; i++) {
        if      (strcmp(all_entries[i].result, "VIOLACAO")          == 0) t_vio++;
        else if (strcmp(all_entries[i].result, "OK")                == 0) t_ok++;
        else if (strcmp(all_entries[i].result, "POSSIVEL VIOLACAO") == 0) t_poss++;
        else t_unk++;
    }

    printf("%-35s  %6d  %8d  %5d  %10d  %10d\n",
           "TOTAL",
           total, t_vio, t_ok, t_poss, t_unk);

    // gera CSV consolidado
    const char *csv_path = "benchmark_relatorio.csv";
    FILE *fp = fopen(csv_path, "w");
    if (!fp) {
        fprintf(stderr, "erro: nao foi possivel criar '%s'\n", csv_path);
    } else {
        // cabeçalho
        time_t now = time(NULL);
        char timebuf[64];
        strftime(timebuf, sizeof(timebuf),
                 "%Y-%m-%d %H:%M:%S", localtime(&now));

        fprintf(fp, "# Tucuman — Benchmark Runner\n");
        fprintf(fp, "# Data           : %s\n", timebuf);
        fprintf(fp, "# Total arquivos : %d\n", argc - 1);
        fprintf(fp, "# Total casos    : %d\n", total);
        fprintf(fp, "# Violacoes      : %d\n", t_vio);
        fprintf(fp, "# OK             : %d\n", t_ok);
        fprintf(fp, "# Poss. Violacao : %d\n", t_poss);
        fprintf(fp, "# Unknown        : %d\n", t_unk);
        fprintf(fp, "#\n");

        fprintf(fp, "Arquivo,ID,Grupo,Tipo,Alinhamento,"
                    "Resultado,Mensagem,Contra-exemplo,Linha\n");

        for (int i = 0; i < total; i++) {
            const VerifierEntry *e = &all_entries[i];
            const char *fname = all_files + i * 256;
            fprintf(fp, "%s,%s,\"%s\",%s,%llu,%s,\"%s\",%s,%d\n",
                    fname,
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
        printf("\nRelatorio consolidado: %s\n", csv_path);
    }

    free(all_entries);
    free(all_files);
    return 0;
}
