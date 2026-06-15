// main.c
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "smt_model.h"
#include "verifier.h"

static const char *group_name[] = {
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

/*static const char *offset_kind_name[] = {
    "CONSTANT",
    "SYMBOLIC"
};*/

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo.c>\n", argv[0]);
        return 1;
    }

    int count = 0;
    ParsedCase *cases = parser_parse_file(argv[1], &count);

    if (!cases || count == 0) {
        fprintf(stderr, "Nenhum padrao reconhecido em '%s'\n", argv[1]);
        return 1;
    }

    printf("=== Tucuman Parser ===\n");
    printf("Arquivo  : %s\n", argv[1]);
    printf("Casos    : %d\n\n", count);

    printf("%-4s  %-12s  %-10s  %-8s  %-10s  %s\n",
           "ID", "Tipo", "Grupo", "Alinhm.", "Offset", "Linha");
    printf("%-4s  %-12s  %-10s  %-8s  %-10s  %s\n",
           "----", "------------", "----------", "--------",
           "----------", "-----");

    for (int i = 0; i < count; i++) {
        ParsedCase *c = &cases[i];

        printf("%-4s  %-12s  %-22s  %4llu B    ",
       c->id,
       c->ptr_type,
       group_name[c->group],
       c->alignment);

        if (c->offset_kind == OFFSET_SYMBOLIC)
            printf("%-10s", "simbolico");
        else
            printf("%-10llu", c->offset);

        printf("  linha %d\n", c->line_number);
    }

    //relatorio
    printf("\n=== Verificacao SMT ===\n");
    printf("%-4s  %-22s  %-10s  %s\n",
        "ID", "Grupo", "Resultado", "Mensagem");
    printf("%-4s  %-22s  %-10s  %s\n",
        "----", "----------------------", "----------", "-------");

    // aloca array de entradas
    VerifierEntry *entries = calloc(count, sizeof(VerifierEntry));
    if (!entries) {
        fprintf(stderr, "erro: sem memoria\n");
        parser_free(cases);
        return 1;
    }

    for (int i = 0; i < count; i++) {
        entries[i] = verifier_check(&cases[i]);
        printf("%-4s  %-22s  %-17s  %s\n",
            entries[i].id,
            entries[i].group,
            entries[i].result,
            entries[i].message);
    }

    // gera CSV
    const char *csv_path = "relatorio.csv";
    if (verifier_write_csv(entries, count, csv_path, argv[1]))
        printf("\nRelatorio gerado: %s\n", csv_path);
    else
        fprintf(stderr, "Erro ao gerar relatorio.\n");

    free(entries);


    printf("\n--- Linhas originais ---\n");
    for (int i = 0; i < count; i++) {
        printf("[%s] %s\n", cases[i].id, cases[i].raw);
    }

    parser_free(cases);
    return 0;
}
