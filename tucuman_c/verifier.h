// verifier.h
#ifndef VERIFIER_H
#define VERIFIER_H

#include "parser.h"
#include "smt_model.h"

// Resultado estruturado do verifier
typedef struct {
    char id[8];
    char group[32];
    char ptr_type[16];
    uint64_t alignment;
    char result[32];
    char message[256];
    char counterexample[32];
    int  line_number;
} VerifierEntry;

// Processa um caso e retorna entrada estruturada
VerifierEntry verifier_check(const ParsedCase *c);

// Gera relatório CSV completo
// entries   — array de VerifierEntry
// count     — número de entradas
// filepath  — caminho do arquivo CSV de saída
// src_file  — arquivo C analisado (para cabeçalho do relatório)
int verifier_write_csv(const VerifierEntry *entries,
                       int count,
                       const char *filepath,
                       const char *src_file);

#endif