// parser.h
#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

typedef enum {
    GROUP_A,
    GROUP_B,
    GROUP_C,
    GROUP_D,
    GROUP_E,
    GROUP_F,
    GROUP_G,
    GROUP_H,
    GROUP_I,
    GROUP_J
} CastGroup;

typedef enum {
    OFFSET_CONSTANT,
    OFFSET_SYMBOLIC
} OffsetKind;

typedef struct {
    char        id[8];
    char        ptr_type[16];
    char        struct_name[64];
    char        field_name[64];
    char        var_name[64];
    uint64_t    alignment;
    uint64_t    offset;
    uint64_t    sym_upper_bound;   // Grupo E — limite superior de i
    OffsetKind  offset_kind;
    CastGroup   group;
    int         is_packed;
    int         line_number;
    char        raw[256];
} ParsedCase;

ParsedCase *parser_parse_file(const char *filepath, int *count);
void        parser_free(ParsedCase *cases);
uint64_t    parser_alignment_of(const char *type_name);

#endif