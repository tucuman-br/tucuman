// smt_model.h
#ifndef SMT_MODEL_H
#define SMT_MODEL_H

#include "parser.h"
#include <z3.h>

typedef enum {
    SMT_VIOLATION,           // UNSAT — violação confirmada
    SMT_OK,                  // SAT   — alinhamento garantido
    SMT_POSSIBLE_VIOLATION,  // SAT com contra-exemplo — offset simbólico
    SMT_UNKNOWN              // solver não conseguiu determinar
} SmtResult;

typedef struct {
    SmtResult   result;
    char        message[256];
    uint64_t    counterexample;
    int         has_counterexample;
} SmtOutput;

// Verifica alinhamento para um caso parseado
SmtOutput smt_check(const ParsedCase *c);

#endif